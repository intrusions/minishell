/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execving.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:33:17 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/25 01:33:46 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	forking(t_command *cmd)
{
	if (cmd->fd_in)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return ;
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return ;
	}
	if (cmd->fd_in)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (execve(cmd->arg->path, cmd->arg->argz, cmd->envp_char) == -1)
		return ;
}

void	exec_token(t_command *cmd)
{
	cmd->envp_char = envp_to_char(cmd->env);
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (!cmd->arg->pid)
		forking(cmd);
	else
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
