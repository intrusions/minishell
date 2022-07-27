/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:07:18 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/27 02:32:38 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

void	remove_env(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*ptr;

	tmp = (*env);
	ptr = tmp;
	if (tmp && !ft_strcmp(name, tmp->name))
	{
		(*env) = tmp->next;
		free(tmp);
		tmp = (*env);
		ptr = (*env);
	}
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			ptr->next = tmp->next;
			free(tmp);
			tmp = ptr;
		}
		ptr = tmp;
		tmp = tmp->next;
	}
}

void	exec_unset(t_command *cmd)
{
	char	*name;

	name = get_name(cmd->arg->argz[1]);
	remove_env(name, &cmd->env);
}
