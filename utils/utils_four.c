/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:37:00 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 00:43:46 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	strnstr_int(char *str, char *to_find)
{
	int	i;
	int	j;

	if (to_find[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

bool	is_whitespace(char c)
{
	if (c == ' ' && c == '\t' && c == '\v'
		&& c == '\n' && c == '\r' && c == '\f')
		return (1);
	return (0);
}

void	writing_error(char *str, int num)
{
	if (num == 1)
	{
		write(2, "groshell: ", 11);
		if (str)
			write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
	if (num == 2)
	{
		write(2, "groshell: ", 11);
		if (str)
			write(2, str, ft_strlen(str));
		write(2, ": no such file or directory\n",
			ft_strlen(": no such file or directory\n"));
	}
	if (num == 3)
	{
		write(2, "groshell: ", 11);
		if (str)
			write(2, str, ft_strlen(str));
		write(2, ": permission denied\n", ft_strlen(": permission denied\n"));
	}
}

void	writing(char *intro, char *content)
{
	write(1, "\n", 1);
	write(1, intro, ft_strlen(intro));
	write(1, content, ft_strlen(content));
	write(1, "\n", 1);
}
