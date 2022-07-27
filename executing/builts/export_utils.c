/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 03:39:01 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 03:39:03 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

bool	is_export(char c)
{
	if (c == 'e' || c == 'x' || c == 'p' || c == 'o' || c == 'r' || c == 't')
		return (1);
	return (0);
}

bool	check_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	check_export(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (check_equal(str) == 0)
		return (printf("no equal"), 0);
	while (str[i] && is_whitespace2(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	j = 0;
	while (str[i + j] && str[i + j] != '=')
		j++;
	if (j == 0)
		return (printf("incorrect export format"), 0);
	j++;
	k = 0;
	while (str[i + j + k])
		k++;
	if (k == 0)
		return (printf("incorrect export format"), 0);
	return (1);
}

char	*export_name(char *str)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	while (str[i] && is_whitespace2(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	while (str[i] && is_whitespace2(str[i]))
		i++;
	j = 0;
	while (str[i + j] && str[i + j] != '=')
		j++;
	name = (char *)malloc(sizeof(char) * (j + 1));
	if (!name)
		return (NULL);
	name[j] = 0;
	j = -1;
	while (str[i + ++j] && str[i + j] != '=')
		name[j] = str[i + j];
	return (name);
}

char	*export_content(char *str)
{
	char	*content;
	int		i;
	int		j;

	i = 0;
	while (str[i] && is_whitespace2(str[i]))
		i++;
	while (str[i] && is_export(str[i]))
		i++;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	j = 0;
	while (str[i + j])
		j++;
	content = (char *)malloc(sizeof(char) * (j + 1));
	if (content == NULL)
		return (NULL);
	content[j] = '\0';
	j = -1;
	while (str[i + ++j])
		content[j] = str[i + j];
	return (content);
}
