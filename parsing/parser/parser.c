/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:29:37 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/24 22:32:16 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

bool	redirection_validation(t_first *uno)
{
	t_first	*tmp;

	tmp = uno->next;
	while (tmp)
	{
		if (tmp->type == APPEND || tmp->type == WRITE || tmp->type == READ || tmp->type == HEREDOC)
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

bool	pipes_validation(t_first *uno)
{
	t_first	*tmp;

	tmp = uno->next;
	if (tmp && tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || tmp->next->type == PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

bool	parser(t_first *uno)
{
	if (!redirection_validation(uno))
		return (write(1, "syntax error\n", 13), 0);
	if (!pipes_validation(uno))
		return (write(1, "syntax error\n", 13), 0);
	return (1);
}
