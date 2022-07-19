/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:45:06 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/19 13:50:30 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_negativ_space(t_cmd *cmd)
{
	int			quote;
	int			i;

	i = 0;
	quote = 0;
	while (cmd->initial_cmd[i])
	{
		quote = what_state(cmd->initial_cmd, i);
		if (cmd->initial_cmd[i] == ' ' && quote)
			cmd->initial_cmd[i] *= -1;
		i++;
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

int	delete_all_space(t_cmd *cmd)
{
	char	**split;

	turn_negativ_space(cmd);
	split = ft_split(cmd->initial_cmd, ' ');
	if (!split)
		return (0);
	cmd->initial_cmd = concat_string_splitted(split);
	if (!cmd->initial_cmd)
		return (0);
	replace_negativ_char(cmd->initial_cmd);
	return (1);
}
