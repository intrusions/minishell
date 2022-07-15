/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:30:56 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/15 04:50:14 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	j;

	j = 0;
	if (n == 0)
		return (0);
	while ((s1[j] || s2[j]) && j < n)
	{
		if (s1[j] != s2[j])
			return ((unsigned char)s1[j] - (unsigned char)s2[j]);
		j++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	is_whitespace(char c)
{
	if ((c >= 8 && c <= 13) || (c == ' '))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)
		|| (c >= 48 && c <= 57) || (c == '$'))
		return (1);
	return (0);
}

void	print_list(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	int			i;
	int			j;

	i = 1;
	tmp = *lst;
	while (tmp)
	{
		j = 1;
		printf("Le maillon %d de la chaine t_all_cmd (spliter par des \";\") :%s\n", i, tmp->initial_cmd);
		while (tmp->cmd_cuted)
		{
			printf("Le maillon %d de la chaine t_piped (spliter par des \"|\")   :%s\n", j, tmp->cmd_cuted->cmd_cuted_by_pipe);
			tmp->cmd_cuted = tmp->cmd_cuted->next;
			j++;
		}
		i++;
		tmp = tmp->next;
	}
}
