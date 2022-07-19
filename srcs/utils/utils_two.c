/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:28:05 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 12:20:35 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_negativ_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

void	replace_negativ_char_piped(t_piped *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		while (lst->cmd_cuted_by_pipe[i])
		{
			if (lst->cmd_cuted_by_pipe[i] < 0)
				lst->cmd_cuted_by_pipe[i] *= -1;
			i++;
		}
		lst = lst->next;
	}
}

void	parse_dollars(t_cmd *cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (cmd->initial_cmd[i])
	{
		quote = what_state(cmd->initial_cmd, i);
		if (cmd->initial_cmd[i] == '$' && quote == 1)
			cmd->initial_cmd[i] *= -1;
		i++;
	}
}

int	what_state(char *str, int j)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i <= j)
	{
		if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		if (str[i] == '\"' && quote == 2)
			quote = 0;
		else if (str[i] == '\"' && quote == 0)
			quote = 2;
		i++;
	}
	return (quote);
}
