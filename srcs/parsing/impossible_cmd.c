/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impossible_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:40 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 15:23:57 by xel              ###   ########.fr       */
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

	i = 0;
	quote = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if (str[i] == '|' && !quote)
		{
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

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
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

int	redir_oppose(char *str)
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

int	check_impossible_cmd(t_cmd *cmd)
{
	negative_pipe_in_quote(cmd->initial_cmd);
	if (!check_multiple_pipe(cmd->initial_cmd))
		return (0);
	replace_negativ_char(cmd->initial_cmd);

	if (!multiple_redir(cmd->initial_cmd))
		return (printf("cest multiple redir\n"), 0);
	if (!pipe_with_redir_after(cmd->initial_cmd))
		return (printf("cest after\n"), 0);
	if (!pipe_with_redir_before(cmd->initial_cmd))
		return (printf("cest before\n"), 0);
	if (!redir_oppose(cmd->initial_cmd))
		return (printf("cest opposer\n"), 0);
	return (1);
}
