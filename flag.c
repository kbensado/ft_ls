/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:05:13 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:36:23 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		set_env(char *pwd, char *path)
{
	int		i;
	int		j;

	i = 4;
	j = 0;
	ft_bzero(pwd, BUFF_SIZE);
	while (path[i])
	{
		pwd[j] = path[i];
		i++;
		j++;
	}
	pwd[j] = '/';
}

int			into_this(t_flag *list, char c)
{
	if (c == 'a')
		list->a = 1;
	else if (c == 'F')
		list->b_f = 1;
	else if (c == 'l')
		list->l = 1;
	else if (c == 'r')
		list->l_r = 1;
	else if (c == 'R')
		list->b_r = 1;
	else if (c == 's')
		list->l_s = 1;
	else if (c == 'S')
		list->b_s = 1;
	else if (c == 't')
		list->t = 1;
	else
		return (0);
	return (1);
}

int			get_flag(t_flag *list, char **arg, int i, char **env)
{
	int		j;
	char	test[1];

	j = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		while (arg[i][j])
		{
			if (arg[i][j] == '-')
				exit(ft_error(ERROR_USAGE, 1));
			if (into_this(list, arg[i][j]) == 0)
			{
				test[0] = arg[i][j];
				exit(ft_error(test, 0));
			}
			j++;
		}
		j = 1;
		i++;
	}
	set_env(list->pwd, env[12]);
	return (i);
}
