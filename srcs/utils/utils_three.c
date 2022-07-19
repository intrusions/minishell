/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:20:20 by xel               #+#    #+#             */
/*   Updated: 2022/07/19 12:20:20 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_syntax_error(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if ((str[i] == ';' && quote) || (str[i] == '\\' && quote))
			str[i] *= -1;
		else if ((str[i] == ';' && !quote) || (str[i] == '\\' && !quote))
			return (0);
		i++;
	}
	return (quote == 0);
}
