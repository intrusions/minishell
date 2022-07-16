/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impossible_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:06:40 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 19:58:27 by jucheval         ###   ########.fr       */
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

void	turn_neg_pipe_in_quote(t_all_cmd **lst)
{
	int		i;
	int		quote;
	char	*str;

	i = 0;
	quote = 0;
	str = (*lst)->initial_cmd;
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
		if ((str[i] == '|' && quote))
			str[i] *= -1;
		i++;
	}
}

int	check_impossible_cmd(t_all_cmd **lst)
{
	t_all_cmd	*tmp;

	tmp = *lst;
	turn_neg_pipe_in_quote(lst);
	while (tmp)
	{
		if (!check_multiple_pipe(tmp->initial_cmd))
			return (printf("multiple pipe detected\n"), 0);
		// if (!redir_last_char(tmp->initial_cmd))
		// 	return (printf("syntax error near unexpected token newline\n"), 0);
		tmp = tmp->next;
	}
	replace_negativ_char_cmd(lst);
	return (1);
}
