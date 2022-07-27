/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:10:15 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/27 02:33:23 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	closing_fd(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->fd_in && tmp->fd_in != 1)
			close(tmp->fd_in);
		if (tmp->fd_out && tmp->fd_out != 1)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
}

void	waitpiding(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->arg)
			waitpid(tmp->arg->pid, 0, 0);
		tmp = tmp->next;
	}
}

t_env	*exec_command(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	if (!redirectionning(tmp))
		return (NULL);
	while (tmp)
	{
		if (!parse_argument(tmp))
		{
			if (tmp && tmp->next)
				tmp->next->fd_in = -1;
		}
		else
		{
			if (check_builts(tmp->arg->argz))
			{
				if (check_builts_nofork(tmp->arg->argz))
					exec_token_builts_nofork(tmp);
				else
					exec_token_builts(tmp);
			}
			else
				exec_token(tmp);
		}
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	waitpiding(cmd);
	closing_fd(cmd);
	return (NULL);
}
