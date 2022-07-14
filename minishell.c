/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:11:38 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/14 04:01:18 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int				count;
	char			*str;
	t_all_cmd		*lst;
	t_env			*env_lst;

	(void)ac;
	(void)av;
	env_lst = env_to_list(env);
	str = malloc(sizeof(char) * 4096);
	while (TRUE)
	{
		write(1, "groshell> ", 10);
		count = read(1, str, 4096);
		str[count] = 0;
		if (!ft_strncmp(str, "exit", 4) && (ft_strlen(str) == 5))
			break ;
		lst = creat_list(str);
		if (start_parsing(&lst, env_lst))
			print_list(&lst);
	}
	return (0);
}
