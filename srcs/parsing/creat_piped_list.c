/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_piped_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:13:49 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/18 19:47:47 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	negative_pipe_in_quote(char *str)
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
		if ((str[i] == '|' && quote))
			str[i] *= -1;
		i++;
	}
}

t_piped	*creat_one_piped_list(char *str)
{
	int			i;
	char		**piped_tab;
	t_piped		*lst;
	t_piped		*tmp;

	i = 0;
	piped_tab = ft_split(str, '|');
	if (!piped_tab)
		return (NULL);
	lst = new_piped_lst(piped_tab[i++]);
	if (!lst)
		return (NULL);
	while (piped_tab[i])
	{
		tmp = new_piped_lst(piped_tab[i]);
		if (!tmp)
			return (NULL);
		add_back_piped_lst(&lst, tmp);
		i++;
	}
	return (lst);
}

int	creat_all_piped_list(t_all_cmd **cmd_list)
{
	t_all_cmd	*tmp;

	tmp = *cmd_list;
	while (tmp)
	{
		negative_pipe_in_quote(tmp->initial_cmd);
		tmp->cmd_cuted = creat_one_piped_list(tmp->initial_cmd);
		if (!tmp->cmd_cuted)
			return (0);
		tmp = tmp->next;
	}
	tmp = *cmd_list;
	while (tmp)
	{
		replace_negativ_char_piped(tmp->cmd_cuted);
		if (!del_piped_space(tmp->cmd_cuted))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
