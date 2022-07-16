/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 21:03:24 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 19:04:51 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	start_parsing(t_all_cmd **lst, t_env *env)
{
	if (!check_impossible_cmd(lst))
		return (0);
	if (!replace_all_variable(lst, env))
		return (0);
	if (!creat_all_piped_list(lst))
		return (0);
	if (!del_quotes(lst))
		return (0);
	if (!check_all_redir(lst))
		return (0);
	return (1);
}
