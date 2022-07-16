/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:28:05 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 18:48:48 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_space(t_all_cmd **lst)
{
	t_all_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp->initial_cmd = ft_strtrim(tmp->initial_cmd, " ");
		if (!tmp->initial_cmd)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

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

void	replace_negativ_char_cmd(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	int			i;

	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (tmp->initial_cmd[i])
		{
			if (tmp->initial_cmd[i] < 0)
				tmp->initial_cmd[i] *= -1;
			i++;
		}
		tmp = tmp->next;
	}
}

void	replace_negativ_char_piped(t_piped *lst)
{
	int			i;

	while (lst)
	{
		i = 0;
		while (lst->cmd_cuted_by_pipe[i])
		{
			if (lst->cmd_cuted_by_pipe[i] < 0)
				lst->cmd_cuted_by_pipe[i] *= -1;
			i++;
		}
		lst = lst->next;
	}
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
