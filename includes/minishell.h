/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:12:26 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/16 16:46:49 by jucheval         ###   ########.fr       */
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
// Check if quote are not closed, " ; " or " \ " , " and turn neg in quote
int			check_syntax_error(char *str);
// Function de delete all space at the start and the end of all cmd in the list
int			del_space(t_all_cmd **lst);
// Function de delete all space at the start and the end of all cmd in the list
int			del_piped_space(t_piped *lst);
// Function to replace variable by their value
int			replace_all_variable(t_all_cmd **lst, t_env *env);
// Function to replace environement variable without quote
int			replace_variable_without_quote(t_all_cmd **lst, t_env *env);
// Function to creat a new string replacing $variable with his value 
char		*string_with_var_value(char *cmd, char *name, int size_old_var);
// Function to find the value in environement variable with only his name
char		*find_variable_value(char *name, t_env *env);
// Function to call a lot of another function, to check impossible case
int			check_impossible_cmd(t_all_cmd **lst);
// Function to check if multiple pire are present in command
int			check_multiple_pipe(char *str);
// Function to check if cmd contain 3 or more right redirection " > "
int			check_triple_redir(char *str);
// Function to creat a chained list, with command splitted by " | "
t_piped		*creat_one_piped_list(char *str);
// Function to creat a chained list s_piped, for all link in s_all_cmd list
int			creat_all_piped_list(t_all_cmd **cmd_list);
// Function to call another secondary function for check all possible redir
int			check_all_redir(t_all_cmd **lst);
// Function to check if triple redir is present in all chained list
int			check_triple_redir_right(t_all_cmd **lst);
// Function to check if triple redir is present in one link
int			check_triple_redir_by_pipe_right(char *str);


int del_double_quotes(t_all_cmd ** lst);


// ========================================================================= //
//                                   Utils                                   //
// ========================================================================= //

// Classic
void		print_list(t_all_cmd **lst);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
bool		is_whitespace(char c);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *str, char c);
char		*ft_strtrim(const char *s1, const char *set);
int			ft_isalnum(int c);
void		replace_negativ_char_piped(t_piped *lst);
void		replace_negativ_char_cmd(t_all_cmd **lst);

// Chained list
t_env		*new_env_lst(char *name, char *content);
void		add_back_env_lst(t_env **lst, t_env *new);
t_all_cmd	*new_lst(char *initial_cmd);
void		add_back_lst(t_all_cmd **lst, t_all_cmd *new);
t_piped		*new_piped_lst(char *cmd_cuted_by_pipe);
void		add_back_piped_lst(t_piped **lst, t_piped *new);

#endif