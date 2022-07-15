/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:28:05 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/15 05:28:32 by jucheval         ###   ########.fr       */
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
