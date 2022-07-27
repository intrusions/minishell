/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:34:47 by nimrod            #+#    #+#             */
/*   Updated: 2022/07/27 03:06:05 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_token	*last_redir(t_command *cmd)
{
	t_token	*tmp;
	t_token	*the_one;

	tmp = cmd->redir;
	the_one = NULL;
	while (tmp)
	{
		if (tmp->type == APPEND || tmp->type == WRITE)
		{
			if (!check_fd_out(tmp))
				return (0);
			the_one = tmp;
		}
		tmp = tmp->next;
	}
	return (the_one);
}

int	init_fd_out(t_command *cmd)
{
	t_token	*redir;

	(void)redir;
	(void)cmd;
	redir = last_redir(cmd);
	if (redir)
	{
		if (redir->type == APPEND)
			cmd->fd_out = opening_append(redir->content);
		if (redir->type == WRITE)
			cmd->fd_out = opening_standard_output(redir->content);
	}
	if (cmd->next)
		piping(cmd, redir);
	if (!redir && !cmd->next)
		cmd->fd_out = 1;
	return (1);
}

void	piping(t_command *cmd, t_token *redir)
{
	if (pipe(cmd->fd) == -1)
		return ;
	if (!redir)
		cmd->fd_out = cmd->fd[1];
	else
		close (cmd->fd[1]);
	cmd->next->fd_in = cmd->fd[0];
	cmd->next->is_piped = 1;
}

int	redirectionning(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (init_fd_in(tmp) == 0)
			return (0);
		if (init_fd_out(tmp) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
