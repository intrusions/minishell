/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_piped_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:13:49 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 12:16:02 by xel              ###   ########.fr       */
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

void	negative_pipe_in_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = what_state(str, i);
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

int	creat_all_piped_list(t_cmd *cmd)
{
	negative_pipe_in_quote(cmd->initial_cmd);
	cmd->cmd_cuted = creat_one_piped_list(cmd->initial_cmd);
	if (!cmd->cmd_cuted)
		return (0);
	replace_negativ_char_piped(cmd->cmd_cuted);
	if (!del_piped_space(cmd->cmd_cuted))
		return (0);
	return (1);
}
