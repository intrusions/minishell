/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:22:08 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/27 22:45:56 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_all(t_command *cmd)
{
	t_command	*tmp_cmd;
	t_token	*tmp_tkn;

	tmp_cmd = cmd;
	while (tmp_cmd != NULL)
	{
		tmp_tkn = tmp_cmd->arg;
		if (tmp_tkn != NULL)
		{
			printf("the arg is :%s\n", tmp_tkn->content);
			tmp_tkn = tmp_tkn->next;
			while (tmp_tkn != NULL)
			{				
				printf ("with option :%s\n", tmp_tkn->content);
				tmp_tkn = tmp_tkn->next;
			}
		}
		tmp_tkn = tmp_cmd->redir;
		if (tmp_tkn != NULL)
		{
			write(1, "the redirection is a ", 21);
			if (tmp_tkn->type == WRITE)
				write(1, "write ", 6);
			if (tmp_tkn->type == HEREDOC)
				write(1, "heredoc ", 8);
			if (tmp_tkn->type == READ)
				write(1, "read ", 5);
			if (tmp_tkn->type == APPEND)
				write(1, "append ", 7);
			write(1, tmp_tkn->content, ft_strlen(tmp_tkn->content));
			tmp_tkn = tmp_tkn->next;
			while (tmp_tkn != NULL)
			{		
				write(1, "\n", 1);		
				write(1, "the next redirection is a ", 27);
				if (tmp_tkn->type == WRITE)
					write(1, "write ", 6);
				if (tmp_tkn->type == HEREDOC)
					write(1, "heredoc ", 8);
				if (tmp_tkn->type == READ)
					write(1, "read ", 5);
				if (tmp_tkn->type == APPEND)
					write(1, "append ", 7);
				write(1, tmp_tkn->content, ft_strlen(tmp_tkn->content));
				tmp_tkn = tmp_tkn->next;
			}
			write(1, "\n", 1);
		}
		if (tmp_cmd->next != NULL)
			printf("next command%s", " ");
		tmp_cmd = tmp_cmd->next;
	}
}

int	working_magic(char *str, t_env **env)
{
	t_command	*cmd;
	t_first		*uno;
	t_env		*tmp;

	uno = lexer(str);
	if (uno->next)
	{
		// // debut
		// t_first *tmpp;

		// tmpp = uno;
		// while (tmpp)
		// {
		// 	printf("ici ma commande :%s\n", tmpp->content);
		// 	tmpp = tmpp->next;
		// }
		// //fin
		if (parser(uno))
		{
			cmd = step_two(uno, *env);
			if (cmd)
			{
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
	char		*str;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = env_to_list(envp);
	if (!env)
		return (0);
	while (true)
	{
		str = readline("groshell> ");
        add_history(str);
		if (!(ft_strncmp(str, "exit", 4)) && ft_strlen(str) == 5)
			break ;
		working_magic(str, &env);

	}
	return (0);
}
