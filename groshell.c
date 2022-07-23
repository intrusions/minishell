/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/24 00:21:14 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	replace_negativ_char(t_command *cmd)
{
	int			i;
	t_command	*tmp;
	t_token		*tmp_token;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp_token = tmp->arg;
		while (tmp_token)
		{
			i = 0;
			while (tmp_token->content[i])
			{
				if (tmp_token->content[i] < 0)
					tmp_token->content[i] *= -1;
				i++;
			}
			tmp_token = tmp_token->next;
		}
		tmp = tmp->next;
	}
}

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)
		|| (c >= 48 && c <= 57) || (c == '$'))
		return (1);
	return (0);
}

int	what_state(char *str, int j)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i <= j)
	{
		if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		if (str[i] == '\"' && quote == 2)
			quote = 0;
		else if (str[i] == '\"' && quote == 0)
			quote = 2;
		i++;
	}
	return (quote);
}

void	parse_dollars(t_command *cmd)
{
	int			i;
	int			quote;
	t_command	*tmp;
	t_token		*tmp_arg;

	quote = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp_arg = tmp->arg;
		while (tmp_arg)
		{
			i = 0; 
			while (tmp_arg->content[i])
			{
				quote = what_state(tmp_arg->content, i);
				if (tmp_arg->content[i] == '$' && quote == 1)
					tmp_arg->content[i] *= -1;
				i++;
			}
			tmp_arg = tmp_arg->next;
		}
		tmp = tmp->next;
	}
}

char	*find_variable_value(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, &name[1], (ft_strlen(name) - 1)) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*string_with_var_value(char *cmd, char *name, int size_old_var)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	dest = malloc(sizeof(char) * ((ft_strlen(cmd) - size_old_var) + \
	ft_strlen(name) + 1));
	if (!dest)
		return (NULL);
	while (cmd[i] && cmd[i] != '$')
		dest[j++] = cmd[i++];
	while (name[k])
		dest[j++] = name[k++];
	while (cmd[i] && ft_isalnum(cmd[i]))
		i++;
	while (cmd[i])
		dest[j++] = cmd[i++];
	return (dest);
}

char	*replace_one_variable(char *str, t_env *env, int i)
{
	int		j;
	char	*variable_name;

	j = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
		j++;
	}
	variable_name = malloc(sizeof(char) * (j + 1));
	if (!variable_name)
		return (NULL);
	i -= j;
	j = 0;
	while (str[i] && ft_isalnum(str[i]))
		variable_name[j++] = str[i++];
	variable_name[j] = 0;
	variable_name = find_variable_value(variable_name, env);
	if (!variable_name)
		return (0);
	str = string_with_var_value(str, variable_name, j);
	if (!str)
		return (NULL);
	return (str);
}

int	replace_variable(t_command *cmd, t_env *env)
{
	int			i;
	t_command	*tmp;
	t_token		*tmp_token;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		tmp_token = tmp->arg;
		while (tmp_token)
		{
			i = 0;
			while (tmp_token->content[i])
			{
				if (tmp_token->content[i] == '$')
				{
					tmp_token->content = \
					replace_one_variable(tmp_token->content, env, i);
					if (!tmp_token->content)
						return (0);
				}
				i++;
			}
			tmp_token = tmp_token->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	replace_all_variable(t_command *cmd, t_env *env)
{
	parse_dollars(cmd);
	if (!replace_variable(cmd, env))
		return (0);
	replace_negativ_char(cmd);
	return (1);
}












int	working_magic(char *str, t_env **env)
{
	t_command	*cmd;
	t_first		*uno;
	t_env		*tmp;

	uno = step_one(str);
	if (uno->next)
	{
		// print_step_one(uno);
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd)
			{
				// print_all(cmd);
				if (!replace_all_variable(cmd, *env))
					return (0);
				tmp = exec_command(cmd);
				if (tmp)
					*env = tmp;
			}
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			count;
	char		*str;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = env_to_list(envp);
	if (!env)
		return (0);
	str = (char *)malloc(sizeof(char) * 4096);
	if (!str)
		return (0);
	while (true)
	{
		write(1, "groshell> ", 10);
		count = read(1, str, 4096);
		str[count] = 0;
		if (!(ft_strncmp(str, "exit", 4)) && ft_strlen(str) == 5)
			break ;
		working_magic(str, &env);
	}
	return (0);
}
