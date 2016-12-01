/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 20:13:01 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/08 02:09:03 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_ascii(char **tab, t_flag *flag)
{
	int		i;

	i = 0;
	while (i != NB_FILE)
	{
		if (i + 1 < NB_FILE && ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			ft_swap_char(&tab[i], &tab[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

void		sort_ascii_rev(char **tab, t_flag *flag)
{
	int		i;

	i = 0;
	while (i != NB_FILE)
	{
		if (i + 1 <= NB_FILE && ft_strcmp(tab[i], tab[i + 1]) < 0)
		{
			ft_swap_char(&tab[i], &tab[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

int			path_is_syml(char *path)
{
	t_stat	l_stat;

	if (lstat(path, &l_stat) == 0)
	{
		if (S_ISLNK(l_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}

int			path_is_block(char *path)
{
	t_stat	l_stat;

	if (lstat(path, &l_stat) == 0)
	{
		if (S_ISBLK(l_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}

int			path_is_socket(char *path)
{
	t_stat	l_stat;

	if (lstat(path, &l_stat) == 0)
	{
		if (S_ISSOCK(l_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}
