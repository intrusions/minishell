/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 21:03:24 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/14 04:22:10 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_all_cmd	*creat_list(char *str)
{
	char		**cmd;
	int			i;
	t_all_cmd	*lst;
	t_all_cmd	*tmp;

	i = 0;
	cmd = ft_split(str, ';');
	lst = new_lst(cmd[i++]);
	while (cmd[i])
	{
		tmp = new_lst(cmd[i]);
		add_back_lst(&lst, tmp);
		i++;
	}
	return (lst);
}

int	check_forbidden_char(t_all_cmd **lst)
{
	int			i;
	int			simple_quote;
	int			double_quote;
	t_all_cmd	*tmp;

	simple_quote = 0;
	double_quote = 0;
	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (tmp->initial_cmd[i])
		{
			if (tmp->initial_cmd[i] == '\'')
				simple_quote++;
			else if (tmp->initial_cmd[i] == '\"')
				double_quote++;
			else if (tmp->initial_cmd[i] == '\\')
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (!(simple_quote % 2 || double_quote % 2));
}

int	del_space(t_all_cmd **lst)
{
	t_all_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp->initial_cmd = ft_strtrim(tmp->initial_cmd, " ");
		if (!tmp->initial_cmd)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	print_list(t_all_cmd **lst)
{
	t_all_cmd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		printf("%s\n", tmp->initial_cmd);
		tmp = tmp->next;
	}
}

int	start_parsing(t_all_cmd **lst, t_env *env)
{
	if (!del_space(lst))
		return (0);
	if (!check_forbidden_char(lst))
		return (printf("syntax error\n"), 0);
	replace_variable_without_quote(lst, env);
	return (1);
}
