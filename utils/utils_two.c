/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:18:22 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 02:07:44 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	word_start(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (is_set(s1[i], set))
		i++;
	return (i);
}

static int	word_end(const char *s1, const char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (is_set(s1[i], set))
		i--;
	return ((ft_strlen(s1) - (i + 1)));
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	diff;
	char	*dest;

	i = 0;
	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	diff = word_start(s1, set) + word_end(s1, set);
	if (diff == (ft_strlen(s1) * 2))
		diff = ft_strlen(s1);
	dest = malloc(sizeof(char) * ((ft_strlen(s1) - diff) + 1));
	if (dest == NULL)
		return (NULL);
	while (is_set(s1[i], set))
		i++;
	while (i < (ft_strlen(s1) - word_end(s1, set)))
	{
		dest[j] = s1[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
