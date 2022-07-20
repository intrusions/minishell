/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impossible_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:40 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 23:40:23 by xel              ###   ########.fr       */
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

int	pipe_with_redir_after(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if (str[i] == '|' && !quote)
		{
			i++;
			if (str[i] == ' ')
				i++;
			if ((str[i] == '<') || (str[i] == '>'))
				return (0);
		}
		i++;
	}
	return (1);
}

int	pipe_with_redir_before(char *str)
{
	int	i;
	int	quote;
	int	last_pos;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (last_pos)
			i = last_pos + 1;
		quote = what_state(str, i);
		if (str[i] == '|' && !quote)
		{
			last_pos = i;
			i--;
			if (str[i] == ' ')
				i--;
			if ((str[i] == '<') || (str[i] == '>'))
				return (0);
		}
		i++;
	}
	return (1);
}

int	multiple_redir(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if ((str[i] == '>' || str[i] == '<') && !quote)
		{
			i++;
			if (str[i] == ' ')
				i++;
			if (str[i] == '<' || str[i] == '>')
			{
				i++;
				if (str[i] == ' ')
					i++;
				if (str[i] == '<' || str[i] == '>')
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_impossible_cmd(t_cmd *cmd)
{
	negative_pipe_in_quote(cmd->initial_cmd);
	if (!check_multiple_pipe(cmd->initial_cmd))
		return (printf("cest multiple pipe\n"), 0);
	replace_negativ_char(cmd->initial_cmd);
	if (!multiple_redir(cmd->initial_cmd))
		return (printf("cest multiple redir\n"), 0);
	if (!pipe_with_redir_after(cmd->initial_cmd))
		return (printf("cest after\n"), 0);
	if (!pipe_with_redir_before(cmd->initial_cmd))
		return (printf("cest before\n"), 0);
	if (!redir_oppose_one(cmd->initial_cmd))
		return (printf("cest opposer one\n"), 0);
	if (!redir_oppose_two(cmd->initial_cmd))
		return (printf("cest opposer two\n"), 0);
	if (!last_char_redir(cmd->initial_cmd))
		return (printf("last char redir\n"), 0);
	if (!first_char_redir(cmd->initial_cmd))
		return (printf("first char redir\n"), 0);
	return (1);
}
