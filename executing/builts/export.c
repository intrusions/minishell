/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:09 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/27 03:06:38 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	add_back_env(char *name, char *content, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_lst(name, content);
}

int	update_env(char *name, char *content, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			tmp->name = name;
			tmp->content = content;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	read_envz(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "=", 1);
		write(1, tmp->content, ft_strlen(tmp->content));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	update_all_envz(t_command *cmd, t_env *env)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		tmp->env = env;
		tmp = tmp->next;
	}
}

void	exec_export(t_command *cmd)
{
	char	*name;
	char	*content;

	if (!check_export(cmd->arg->argz[1]))
		return ;
	name = export_name(cmd->arg->argz[1]);
	content = export_content(cmd->arg->argz[1]);
	if (update_env(name, content, cmd->env))
	{
		update_all_envz(cmd, cmd->env);
		return ;
	}
	add_back_env(name, content, cmd->env);
	update_all_envz(cmd, cmd->env);
}
