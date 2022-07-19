/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 05:04:18 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 02:27:03 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_last_char(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	t_piped		*tmp_piped;
	int			i;

	tmp = *lst;
	while (tmp)
	{
		tmp_piped = tmp->cmd_cuted;
		while (tmp_piped)
		{
			i = 0;
			while (tmp_piped->cmd_cuted_by_pipe[i])
				i++;
			if (tmp_piped->cmd_cuted_by_pipe[i - 1] == '<' || tmp_piped->cmd_cuted_by_pipe[i - 1] == '>')
				return (printf("syntax error near unexpected token 'newline'\n"), 0);
			tmp_piped = tmp_piped->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

// int	check_nb_redir(t_all_cmd **lst)
// {
// 	t_all_cmd	*tmp;
// 	t_piped		*tmp_piped;
// 	int			i;

// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		tmp_piped = tmp->cmd_cuted;
// 		while (tmp_piped)
// 		{
// 			i = 0;
// 			while (tmp_piped->cmd_cuted_by_pipe[i])
// 			{
// 				if (str[i] == '\'' && quote == 1)
// 					quote = 0;
// 				else if (str[i] == '\'' && quote == 0)
// 					quote = 1;
// 				if (str[i] == '\"' && quote == 2)
// 					quote = 0;
// 				else if (str[i] == '\"' && quote == 0)
// 					quote = 2;

// 				if (((tmp_piped->cmd_cuted_by_pipe[i] == '<') || (tmp_piped->cmd_cuted_by_pipe[i] == '>')) && !quote)
// 				{
// 					count++;
// 					i++;
// 				}
// 				if (tmp_piped->cmd_cuted_by_pipe[i] == ' ')
// 					i++;
// 				if (tmp_piped->cmd_cuted_by_pipe[i])
// 			}
// 			tmp_piped = tmp_piped->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }

int	check_all_redir(t_all_cmd **lst)
{
	// if (!check_nb_redir(lst))
	// 	return (0);
	if (!check_redir_last_char(lst))
		return (0);
	return (1);
}
