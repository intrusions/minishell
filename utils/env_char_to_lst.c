/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 01:06:51 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 02:59:50 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_content(char *envp)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	i++;
	while (envp[i + j])
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	str[j] = 0;
	j = -1;
	while (envp[i + ++j])
		str[j] = envp[i + j];
	return (str);
}

char	*get_name(char *envp)
{
	char	*str;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = 0;
	i = -1;
	while (envp[++i] && envp[i] != '=')
		str[i] = envp[i];
	return (str);
}

int	has_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (0);
}

bool	check_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (has_equal(envp[i]) < 1)
			return (printf("wrong env variable"), 0);
	}
	return (1);
}

t_env	*env_to_list(char **envp)
{
	int		i;
	t_env	*env;
	char 	*name;
	char	*content;
	t_env	*tmp;

	if (!envp[0])
		return (printf("no env"), NULL);
	if (!check_envp(envp))
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		name = get_name(envp[i]);
		if (!name)
			return (NULL);
		content = get_content(envp[i]);
		if (!content)
			return (NULL);
		tmp = new_env_lst(name, content);
		if (!tmp)
			return (NULL);
		add_back_env_lst(&env, tmp);
	}
	return (env);
}