/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:44:50 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/27 02:45:12 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int actual_mode(char c)
{
	if (c == '>')
		return (R_REDIR_MODE);
	if (c == '<')
		return (L_REDIR_MODE);
	if (c == '|')
		return (PIPE);
	if (c == '\"')
		return (DQUOTE_MODE);
	if (c == '\'')
		return (SQUOTE_MODE);
	if (c == ' ')
		return (NEUTRAL_MODE);
	else
		return (WORD_MODE);
}

char *alloc_content(char *str, unsigned int size)
{
	char            *alloc;
	unsigned int    i;

	alloc = (char *)malloc(sizeof(char) * (size + 1));
	if (!alloc)
		return (NULL);
	alloc[size] = 0;
	i = -1;
	while (str[++i] && i < size)
		alloc[i] = str[i];
	return (alloc);
}
