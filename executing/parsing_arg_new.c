/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:55:14 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 02:35:32 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool	get_the_path(t_command *cmd)
{
	int		i;
	char	**envp;

	i = 0;
	envp = envp_to_char(cmd->env);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (0);
	cmd->arg->unix_paths = ft_split(&envp[i][4], ':');
	if (!cmd->arg->unix_paths)
		return (0);
	if (!command_trim(cmd))
		return (writing_error(NULL, CMD_NOT_FOUND), 0);
	if (!cmd->arg->command)
		return (0);
	if (is_builts(cmd->arg->command))
		return (1);
	i = 0;
	while (cmd->arg->unix_paths[i] && \
		!find_path(cmd->arg, cmd->arg->unix_paths[i]))
		i++;
	if (!cmd->arg->unix_paths[i])
		return (writing_error(cmd->arg->command, CMD_NOT_FOUND), 0);
	if (!cmd->arg->path)
		return (writing_error(cmd->arg->command, CMD_NOT_FOUND), 0);
	return (1);
}

bool	parse_argument(t_command *cmd)
{
	t_token	*tmp_tkn;
	int		i;
	int		j;

	if (!cmd->arg)
		return (0);
	token_initing(cmd);
	if (!get_the_path(cmd))
		return (0);
	i = 0;
	tmp_tkn = cmd->arg;
	while (tmp_tkn)
	{
		i++;
		tmp_tkn = tmp_tkn->next;
	}
	if (!i)
		return (0);
	cmd->arg->argz = (char **)malloc(sizeof(char *) * (i + 2));
	if (!cmd->arg->argz)
		return (0);
	tmp_tkn = cmd->arg;
	cmd->arg->argz[0] = cmd->arg->command;
	tmp_tkn = tmp_tkn->next;
	j = 0;
	while (++j < i)
	{
		cmd->arg->argz[j] = tmp_tkn->content;
		tmp_tkn = tmp_tkn->next;
	}
	cmd->arg->argz[j] = NULL;
	return (1);
}
