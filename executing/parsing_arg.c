/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:16 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/27 02:36:07 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	token_initing(t_command *cmd)
{
	cmd->arg->unix_paths = NULL;
	cmd->arg->argz = NULL;
	cmd->arg->command = NULL;
	cmd->arg->path = NULL;
}

bool	command_trim(t_command *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (is_whitespace(cmd->arg->content[i]))
		i++;
	while (is_printable_except_space(cmd->arg->content[i + j]))
		j++;
	if (!j)
		return (0);
	cmd->arg->command = (char *)malloc(sizeof(char) * (j + 1));
	if (!cmd->arg->command)
		return (0);
	j = 0;
	while (is_printable_except_space(cmd->arg->content[i + j]))
	{
		cmd->arg->command[j] = cmd->arg->content[i + j];
		j++;
	}
	cmd->arg->command[j] = 0;
	return (1);
}

bool	find_path(t_token *arg, char *unix_path)
{
	char	slash[2];

	slash[0] = '/';
	slash[1] = '\0';
	arg->path = ft_strjoin_new(unix_path, slash, 0);
	if (!arg->path)
		return (0);
	arg->path = ft_strjoin_new(arg->path, arg->command, 1);
	if (!arg->path)
		return (0);
	if (!access(arg->path, X_OK))
		return (1);
	return (free(arg->path), 0);
}

bool	is_builts(char *command)
{
	if (!ft_strncmp(command, "echo", 5))
		return (1);
	if (!ft_strncmp(command, "cd", 3))
		return (1);
	if (!ft_strncmp(command, "pwd", 4))
		return (1);
	if (!ft_strncmp(command, "export", 7))
		return (1);
	if (!ft_strncmp(command, "unset", 6))
		return (1);
	if (!ft_strncmp(command, "env", 4))
		return (1);
	if (!ft_strncmp(command, "exit", 5))
		return (1);
	return (0);
}
