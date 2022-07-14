/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:12:26 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/14 04:56:53 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ========================================================================= //
//                                   Library                                 //
// ========================================================================= //

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "errno.h"

// ========================================================================= //
//                                  Define                                   //
// ========================================================================= //

# define TRUE 1
# define FALSE 0

// ========================================================================= //
//                                 Structure                                 //
// ========================================================================= //

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	char					*what_redir;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_piped
{
	char					*cmd_cuted_by_pipe;
	char					*cmd_with_no_redir;
	struct s_redirection	*redir;
	struct s_piped			*next;
}	t_piped;

typedef struct s_all_cmd
{
	char				*initial_cmd;
	struct s_piped		*cmd_cuted;
	struct s_all_cmd	*next;
}	t_all_cmd;

// ========================================================================= //
//                                 Parsing                                   //
// ========================================================================= //

// Function to creat a chained list with environmment variable
t_env		*env_to_list(char **envp);
// Function to call all other secondary function about parsing
int			start_parsing(t_all_cmd **lst, t_env *env);
// Creat chained list, with command typed in stdin, splited by " ; "
t_all_cmd	*creat_list(char *str);
// Function de delete all space at the start and the ent of all cmd in the list
int			del_space(t_all_cmd **lst);
// Function to check if all quote are x2, and check if an " \ " are present in
int			check_forbidden_char(t_all_cmd **lst);
// Function to replace environement variable without quote
int			replace_variable_without_quote(t_all_cmd **lst, t_env *env);
// Function to creat a new string replacing $variable with his value 
char		*string_with_var_value(char *cmd, char *name, int size_old_var);
// Function to find the value in environement variable with only his name
char		*find_variable_value(char *name, t_env *env);

// ========================================================================= //
//                                   Utils                                   //
// ========================================================================= //

int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *str, char c);
t_all_cmd	*new_lst(char *initial_cmd);
void		add_back_lst(t_all_cmd **lst, t_all_cmd *new);
void		print_list(t_all_cmd **lst);
char		*ft_strtrim(const char *s1, const char *set);
int			ft_isalnum(int c);
t_env		*new_lst_env(char *name, char *content);
void		add_back_lst_env(t_env **lst, t_env *new);

#endif