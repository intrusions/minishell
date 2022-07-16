/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:23:05 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 16:16:04 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parse_dollars(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	int			i;
	int			quote;

	i = 0;
	tmp = *lst;
	quote = 0;
	while (tmp)
	{
		while (tmp->initial_cmd[i])
		{
			if (tmp->initial_cmd[i] == '\'' && quote == 1)
				quote = 0;
			else if (tmp->initial_cmd[i] == '\'' && quote == 0)
				quote = 1;
			if (tmp->initial_cmd[i] == '\"' && quote == 2)
				quote = 0;
			else if (tmp->initial_cmd[i] == '\"' && quote == 0)
				quote = 2;

			if (tmp->initial_cmd[i] == '$' && quote == 1)
				tmp->initial_cmd[i] *= -1;
			i++;
		}
		tmp = tmp->next;
	}
}

int	replace_variable(t_all_cmd **lst, t_env *env)
{
	int			i;
	int			j;
	char		*variable_name;
	t_all_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		j = 0;
		i = 0;
		while (tmp->initial_cmd[i])
		{
			if (tmp->initial_cmd[i] == '$')
			{
				while (tmp->initial_cmd[i] && ft_isalnum(tmp->initial_cmd[i]))
				{
					i++;
					j++;
				}
				variable_name = malloc(sizeof(char) * (j + 1));
				if (!variable_name)
					return (0);
				i -= j;
				j = 0;
				while (tmp->initial_cmd[i] && ft_isalnum(tmp->initial_cmd[i]))
					variable_name[j++] = tmp->initial_cmd[i++];
				variable_name[j] = 0;
				variable_name = find_variable_value(variable_name, env);
				tmp->initial_cmd = string_with_var_value(\
				tmp->initial_cmd, variable_name, j);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	replace_all_variable(t_all_cmd **lst, t_env *env)
{
	parse_dollars(lst);
	if (!replace_variable(lst, env))
		return (0);
	replace_negativ_char_cmd(lst);
	return (1);
}