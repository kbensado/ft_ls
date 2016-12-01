/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 16:59:23 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 01:41:37 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				rec_dir(char *path, t_flag *flag)
{
	DIR				*fd;

	if (!(fd = opendir(path)))
	{
		ft_error(path, 1);
		return ;
	}
	number_of_dir(fd, flag);
	closedir(fd);
}

char				*get_readlink(char *path)
{
	t_stat			l_stat;
	char			*buff;

	buff = NULL;
	if (lstat(path, &l_stat) == 0)
	{
		buff = ft_strnew(l_stat.st_size + 1);
		if (readlink(path, buff, l_stat.st_size + 1))
		{
			return (buff);
		}
	}
	return (NULL);
}

int					path_is_dir2(char *path)
{
	t_stat			l_stat;

	if (stat(path, &l_stat) == 0)
	{
		if (S_ISDIR(l_stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}

void				set_file(char **path, int *cmp, t_flag *flag, int current)
{
	char			*sym;
	static int		key = 0;

	sym = NULL;
	if (current == 1)
		print_dir(".", flag, key);
	while (cmp[0] < cmp[1])
	{
		if (path_is_dir(path[cmp[0]], 0) == 1)
			print_dir(path[cmp[0]], flag, key);
		else if (path_is_syml(path[cmp[0]]) == 1)
		{
			if (!(sym = get_readlink(path[cmp[0]])))
				return ;
			if (path_is_dir2(path[cmp[0]]))
				flag->l == 1 ? SYMLINK : SYMLINK_2;
			else
				WS(sym);
		}
		else
			open_fail(path[cmp[0]], flag);
		cmp[0]++;
		key++;
	}
}
