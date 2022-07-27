/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 03:01:25 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 03:02:35 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	check_fd_in(char *content)
{
	content = ft_strtrim(content, "< ");
	if (access(content, F_OK) != 0)
		return (writing_error(ft_strtrim(content, "> "), NO_FILE), 0);
	if (access(content, R_OK) == -1)
		return (writing_error(ft_strtrim(content, "> "), WRONG_CHMOD), 0);
	return (1);
}

bool	init_fd_in(t_command *cmd)
{
	t_token	*tmp;
	t_token	*the_one;

	tmp = cmd->redir;
	the_one = NULL;
	while (tmp)
	{
		if (tmp->type == HEREDOC || tmp->type == READ)
		{
			if (!check_fd_in(tmp->content))
				return (0);
			the_one = tmp;
		}
		tmp = tmp->next;
	}
	if (the_one)
	{
		if (the_one->type == HEREDOC)
			cmd->fd_in = opening_heredoc(the_one->content);
		if (the_one->type == READ)
			cmd->fd_in = opening_standard_input(the_one->content);
	}
	if (!the_one && !cmd->is_piped)
		cmd->fd_in = 0;
	return (1);
}

bool	check_fd_out(t_token *redir)
{
	int		fd;
	char	*file;

	file = ft_strtrim(redir->content, "> ");
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (writing_error(ft_strtrim(file, "> "), WRONG_CHMOD), 0);
	}
	if (redir != NULL)
	{
		if (redir->type == APPEND)
			fd = open(file, O_CREAT | O_RDWR, 0644);
		if (redir->type == WRITE)
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (writing("cant open file", " "), 0);
		close(fd);
	}
	return (1);
}
