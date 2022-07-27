/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsing_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:28:30 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/25 01:30:38 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	check_builts(char **argz)
{
	if (!ft_strncmp("echo", argz[0], 5))
		return (1);
	if (!ft_strncmp("env", argz[0], 4))
		return (1);
	if (!ft_strncmp("pwd", argz[0], 4))
		return (1);
	if (!ft_strncmp("export", argz[0], 7))
		return (1);
	if (!ft_strncmp("unset", argz[0], 6))
		return (1);
	if (!ft_strncmp("cd", argz[0], 3))
		return (1);
	if (!ft_strncmp("exit", argz[0], 5))
		return (1);
	return (0);
}

void	exec_builts(t_command *cmd)
{
	if (!ft_strncmp(cmd->arg->argz[0], "echo", 5))
		exec_echo(cmd);
	if (!ft_strncmp(cmd->arg->argz[0], "pwd", 4))
		exec_pwd(cmd);
	if (!ft_strncmp(cmd->arg->argz[0], "env", 4))
		exec_env(cmd);
	exit(0);
}

void	forking_builts(t_command *cmd)
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
	exec_builts(cmd);
}

void	exec_token_builts(t_command *cmd)
{
	cmd->arg->pid = fork();
	if (cmd->arg->pid == -1)
		return ;
	if (!cmd->arg->pid)
		forking_builts(cmd);
	else
	{
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
}
