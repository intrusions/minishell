/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:30:56 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 12:08:30 by xel              ###   ########.fr       */
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

void	print_list(t_cmd *cmd)
{
	t_piped		*tmp;
	int			i;
	int			j;

	i = 1;
	j = 1;
	tmp = cmd->cmd_cuted;
	printf("Initial command :%s:\n", cmd->initial_cmd);
	while (tmp)
	{
		printf("Le maillon %d de la chaine t_piped (spliter par des \"|\")   :%s:\n", j, tmp->cmd_cuted_by_pipe);
		tmp = tmp->next;
		j++;
	}
	i++;
}
