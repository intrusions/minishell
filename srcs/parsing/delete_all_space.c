/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:45:06 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/18 20:22:50 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_negativ_space(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	int			quote;
	int			i;

	i = 0;
	quote = 0;
	tmp = *lst;
	while (tmp)
	{
		while (tmp->initial_cmd[i])
		{
			if (tmp->initial_cmd[i] == '\'' && quote == 1)
				quote = 0;
			else if (tmp->initial_cmd[i] == '\'' && quote == 0)
				quote = 1;
			if (tmp->initial_cmd[i] == '\"' && quote == 2)
				quote = 0;
			else if (tmp->initial_cmd[i] == '\"' && quote == 0)
				quote = 2;
			if (tmp->initial_cmd[i] == ' ' && quote)
				tmp->initial_cmd[i] *= -1;
			i++;
		}
		tmp = tmp->next;
	}
}

int	count_string_without_space(char **split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split[i])
	{
		count += ft_strlen(split[i]) + 1;
		i++;
	}
	return (count + 1);
}

char	*concat_string_splitted(char **split)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = 0;
	k = 0;
	dest = malloc(sizeof(char) * (count_string_without_space(split) + 1));
	if (!dest)
		return (NULL);
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			dest[k] = split[i][j];
			k++;
			j++;
		}
		if (split[i + 1])
			dest[k++] = ' ';
		i++;
	}
	dest[k] = 0;
	return (dest);
}

int	delete_all_space(t_all_cmd **lst)
{
	t_all_cmd	*tmp;
	char		**split;

	tmp = *lst;
	turn_negativ_space(lst);
	split = ft_split(tmp->initial_cmd, ' ');
	tmp->initial_cmd = concat_string_splitted(split);
	replace_negativ_char_cmd(lst);
	return (1);
}
