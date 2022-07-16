/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_double_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:25:52 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 17:23:11 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	negativ_double_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 1)
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		if (str[i] == '\"' && quote == 2)
			quote = 0;
		else if (str[i] == '\"' && quote == 0)
			quote = 2;
		if (str[i] == '\"' && quote == 1)
			str[i] *= -1;
		i++;
	}
}

char	*del_neg_quotes(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			j++;
		i++;
	}
	dest = malloc(sizeof(char) * ((i - j) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			dest[j++] = str[i++];
		else
			i++;
	}
	dest[i] = 0;
	return (dest);
}

int del_double_quotes(t_all_cmd ** lst)
{
	t_all_cmd	*tmp;
	t_piped		*tmp_cuted;

	tmp = *lst;
	while (tmp)
	{
		tmp_cuted = tmp->cmd_cuted;
		while (tmp_cuted)
		{
			negativ_double_quote(tmp_cuted->cmd_cuted_by_pipe);
			tmp_cuted = tmp_cuted->next;
		}
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp)
	{
		tmp_cuted = tmp->cmd_cuted;
		while (tmp_cuted)
		{
			tmp_cuted->cmd_cuted_by_pipe = del_neg_quotes(tmp_cuted->cmd_cuted_by_pipe);
			if (!tmp_cuted->cmd_cuted_by_pipe)
				return (0);
			tmp_cuted = tmp_cuted->next;
		}
		tmp = tmp->next;
	}
	replace_negativ_char_piped((*lst)->cmd_cuted);
	return (1);
}
