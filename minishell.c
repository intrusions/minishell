/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:11:38 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 11:46:23 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int				count;
	char			*str;
	t_env			*env_lst;
	t_cmd			*cmd;

	(void)ac;
	(void)av;
	cmd = malloc(sizeof(cmd));
	env_lst = env_to_list(env);
	str = malloc(sizeof(char) * 4096);
	while (TRUE)
	{
		write(1, "groshell> ", 10);
		count = read(1, str, 4096);
		str[count - 1] = 0;
		if (!ft_strncmp(str, "exit", 4) && (ft_strlen(str) == 4))
			break ;
		cmd->initial_cmd = str;
		if (cmd->initial_cmd)
		{
			if (start_parsing(cmd, env_lst))
				print_list(cmd);
		}
	}
	return (0);
}
