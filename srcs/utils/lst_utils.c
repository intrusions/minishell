/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:45:43 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/14 03:55:25 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_all_cmd	*new_lst(char *initial_cmd)
{
	t_all_cmd	*new;

	new = malloc(sizeof(t_all_cmd));
	if (!new)
		return (NULL);
	new->initial_cmd = initial_cmd;
	new->next = NULL;
	return (new);
}

void	add_back_lst(t_all_cmd **lst, t_all_cmd *new)
{
	t_all_cmd	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (lst)
		*lst = new;
}
