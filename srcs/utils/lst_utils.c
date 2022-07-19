/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:45:43 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 12:19:30 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_piped	*new_piped_lst(char *cmd_cuted_by_pipe)
{
	t_piped	*new;

	new = malloc(sizeof(t_piped));
	if (!new)
		return (NULL);
	new->cmd_cuted_by_pipe = cmd_cuted_by_pipe;
	new->next = NULL;
	return (new);
}

void	add_back_piped_lst(t_piped **lst, t_piped *new)
{
	t_piped	*tmp;

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
