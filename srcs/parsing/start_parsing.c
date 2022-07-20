/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 21:03:24 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 13:58:17 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	start_parsing(t_cmd *cmd, t_env *env)
{
	if (!check_syntax_error(cmd->initial_cmd))
		return (printf("syntax error\n"), 0);
	if (!delete_all_space(cmd))
		return (0);
	if (!check_impossible_cmd(cmd))
		return (printf("syntax error\n"), 0);
	if (!replace_all_variable(cmd, env))
		return (printf("\n"), 0);
	if (!creat_all_piped_list(cmd))
		return (0);
	if (!del_quotes(cmd))
		return (0);
	return (1);
}
