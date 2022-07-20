/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impossible_cmd_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:31:05 by xel               #+#    #+#             */
/*   Updated: 2022/07/19 23:31:05 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_oppose_one(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if (str[i] == '>' && !quote)
		{
			i++;
			if (str[i] == ' ')
				i++;
			if (str[i] == '<')
				return (0);
		}
		i++;
	}
	return (1);
}

int	redir_oppose_two(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if (str[i] == '<' && !quote)
		{
			i++;
			if (str[i] == ' ')
				i++;
			if (str[i] == '>')
				return (0);
		}
		i++;
	}
	return (1);
}

int	last_char_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i && !str[i] && (str[i - 1] == '<' || str[i - 1] == '>'))
		return (0);
	return (1);
}

int	first_char_redir(char *str)
{
	return (!(str[0] == '>') && !(str[0] == '|'));
}
