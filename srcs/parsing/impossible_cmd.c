/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impossible_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:40 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/15 05:27:02 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_multiple_pipe(char *str)
{
	int	i;
	int	nb_pipe;

	i = 0;
	while (str[i])
	{
		nb_pipe = 0;
		while (str[i] && str[i] != '|')
			i++;
		if (str[i] == '|')
		{
			nb_pipe++;
			i++;
		}
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i] == '|')
			nb_pipe++;
		if (nb_pipe == 2)
			return (0);
	}
	return (1);
}

int	check_impossible_cmd(t_all_cmd **lst)
{
	t_all_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!check_multiple_pipe(tmp->initial_cmd))
			return (printf("multiple pipe detected\n"), 0);
		tmp = tmp->next;
	}
	return (1);
}
