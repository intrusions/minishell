/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/30 22:28:24 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_all(t_command *cmd);

void	working_magic(char *str, t_env **env)
{
	t_command	*cmd;
	t_first		*uno;

	uno = lexer(str);
	if (uno && uno->next)
	{
		if (command_validation(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd)
			{
				if (!replace_all_variable(cmd, *env))
					return ;
				// print_all(cmd);
				exec_command(cmd);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_env	*env;

	(void)argc;
	(void)argv;
	singleton(0, 1);
	env = env_to_list(envp);
	str = (char *)malloc(sizeof(char) * 4096);
	while (1)
	{
		str = readline("groshell> ");
		add_history(str);
		if (!(ft_strncmp(str, "exit", 5)))
			break ;
		working_magic(str, &env);
	}
	return (0);
}
