/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impossible_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:40 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 12:05:17 by xel              ###   ########.fr       */
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
		if (nb_pipe && !str[i])
			return (0);
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i] == '|')
			nb_pipe++;
		if (nb_pipe == 2)
			return (0);
	}
	return (1);
}

// int	check_redir_before_pipe(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] != '|')
// 			i++;
// 		if (str[i] == '|' && (str[i - 1] == '<' && (i > 0)))
// 			return (printf("syntax error near unexpected token \'|\'\n"), 0);
// 		else if ((str[i] == '|' && (str[i - 1] == '>' && (i > 0))))
// 			return (printf("syntax error near unexpected token \'newline\'\n"), 0);
// 		i++;
// 	}
// 	return (1);
// }

int	check_impossible_cmd(t_cmd *cmd)
{
	negative_pipe_in_quote(cmd->initial_cmd);
	if (!check_multiple_pipe(cmd->initial_cmd))
		return (0);
	replace_negativ_char(cmd->initial_cmd);
	return (1);
}
