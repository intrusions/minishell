/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:23:05 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 18:48:36 by jucheval         ###   ########.fr       */
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
	return (str);
}

int	replace_variable(t_all_cmd **lst, t_env *env)
{
	int			i;
	t_all_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (tmp->initial_cmd[i])
		{
			if (tmp->initial_cmd[i] == '$')
			{
				tmp->initial_cmd = \
				replace_one_variable(tmp->initial_cmd, env, i);
				if (!tmp->initial_cmd)
					return (0);
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
