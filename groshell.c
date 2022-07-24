/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/24 22:29:00 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	working_magic(char *str, t_env **env)
{
	t_command	*cmd;
	t_first		*uno;
	t_env		*tmp;

	uno = step_one(str);
	if (uno->next)
	{
		// print_step_one(uno);
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd)
			{
				// print_all(cmd);
				if (!replace_all_variable(cmd, *env))
					return (0);
				tmp = exec_command(cmd);
				if (tmp)
					*env = tmp;
			}
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			count;
	char		*str;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = env_to_list(envp);
	if (!env)
		return (0);
	str = (char *)malloc(sizeof(char) * 4096);
	if (!str)
		return (0);
	while (true)
	{
		write(1, "groshell> ", 10);
		count = read(1, str, 4096);
		str[count] = 0;
		if (!(ft_strncmp(str, "exit", 4)) && ft_strlen(str) == 5)
			break ;
		working_magic(str, &env);
	}
	return (0);
}
