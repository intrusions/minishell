/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:25:52 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 13:41:31 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	negativ_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	while (str[i])
	{
		quote = what_state(str, i);
		if ((str[i] == '\"' && quote == 1) || (str[i] == '\'' && quote == 2))
			str[i] *= -1;
		i++;
	}
}

char	*del_one_neg_quotes(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] == '\"') || (str[i] == '\''))
			j++;
	}
	dest = malloc(sizeof(char) * ((i - j) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			dest[j++] = str[i++];
		else
			i++;
	}
	dest[i] = 0;
	return (dest);
}

int	del_all_neg_quotes(t_cmd *cmd)
{
	t_piped		*tmp_cuted;

	tmp_cuted = cmd->cmd_cuted;
	while (tmp_cuted)
	{
		tmp_cuted->cmd_cuted_by_pipe = \
		del_one_neg_quotes(tmp_cuted->cmd_cuted_by_pipe);
		if (!tmp_cuted->cmd_cuted_by_pipe)
			return (0);
		tmp_cuted = tmp_cuted->next;
	}
	replace_negativ_char_piped(cmd->cmd_cuted);
	return (1);
}

int	del_quotes(t_cmd *cmd)
{
	t_piped		*tmp;

	tmp = cmd->cmd_cuted;
	while (tmp)
	{
		negativ_quote(tmp->cmd_cuted_by_pipe);
		tmp = tmp->next;
	}
	if (!del_all_neg_quotes(cmd))
		return (0);
	return (1);
}
