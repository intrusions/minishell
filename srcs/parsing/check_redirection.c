/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:04:18 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 18:08:56 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_is_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '>')
		return (1);
	return (0);
}

int	check_triple_redir_by_pipe_right(char *str)
{
	int	i;
	int	nb_redir;

	i = 0;
	nb_redir = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			nb_redir++;
			i++;
			while (str[i] && is_whitespace(str[i]) && str[i] != '>')
				i++;
			if (str[i] == '>')
				nb_redir++;
			else
				nb_redir = 0;
		}
		i++;
	}
	if (nb_redir == 3)
		return (printf("syntax error near unexpected token '>'\n"), 0);
	else if (nb_redir >= 4)
		return (printf("syntax error near unexpected token '>>'\n"), 0);
	return (1);
}

int	check_triple_redir_right(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	t_piped		*tmp_piped;

	tmp = *lst;
	while (tmp)
	{
		tmp_piped = (*lst)->cmd_cuted;
		while (tmp_piped)
		{
			if (!check_triple_redir_by_pipe_right(tmp->\
			cmd_cuted->cmd_cuted_by_pipe))
				return (0);
			tmp_piped = tmp_piped->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_all_redir(t_all_cmd **lst)
{
	if (!check_triple_redir_right(lst))
		return (0);
	return (1);
}
