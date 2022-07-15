/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_piped_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:13:49 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/15 04:39:30 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_piped_space(t_piped *lst)
{
	while (lst)
	{
		lst->cmd_cuted_by_pipe = ft_strtrim(lst->cmd_cuted_by_pipe, " ");
		if (!lst->cmd_cuted_by_pipe)
			return (0);
		lst = lst->next;
	}
	return (1);
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
		tmp->cmd_cuted = creat_one_piped_list(tmp->initial_cmd);
		if (!tmp->cmd_cuted)
			return (0);
		tmp = tmp->next;
	}
	tmp = *cmd_list;
	while (tmp)
	{
		if (!del_piped_space(tmp->cmd_cuted))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
