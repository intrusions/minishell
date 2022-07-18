/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:43:14 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/18 19:43:59 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		if (str[i] == '\"' && quote == 2)
			quote = 0;
		else if (str[i] == '\"' && quote == 0)
			quote = 2;
		if ((str[i] == ';' && quote) || (str[i] == '\\' && quote))
			str[i] *= -1;
		else if ((str[i] == ';' && !quote) || (str[i] == '\\' && !quote))
			return (0);
		i++;
	}
	return (quote == 0);
}

t_all_cmd	*creat_list(char *str)
{
	char		**cmd;
	int			i;
	t_all_cmd	*lst;
	t_all_cmd	*tmp;

	i = 0;
	if (!check_syntax_error(str))
		return (printf("syntax error\n"), NULL);
	cmd = ft_split(str, ';');
	if (!cmd)
		return (NULL);
	lst = new_lst(cmd[i++]);
	if (!lst)
		return (NULL);
	while (cmd[i])
	{
		tmp = new_lst(cmd[i]);
		add_back_lst(&lst, tmp);
		i++;
	}
	if (!delete_all_space(&lst))
		return (0);
	return (lst);
}
