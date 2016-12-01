/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 13:14:47 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:48:57 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_ldir(t_ndir *dir)
{
	while (dir)
	{
		WS(dir->path);
		dir = dir->next;
	}
}

int				new_dir(char *path, t_ndir *dir)
{
	while (dir)
	{
		if (ft_strcmp(path, dir->path) == 0 && path_is_dir(path, 0))
			return (0);
		dir = dir->next;
	}
	return (1);
}

t_ndir			*another_dir(t_ndir *n_dir, t_flag *flag, char *path)
{
	DIR			*dir;
	t_dir		*dp;
	char		*buffer;

	if (!(dir = opendir(path)))
	{
		ft_error(path, 1);
		return (n_dir);
	}
	buffer = ft_strnew(BUFF_SIZE);
	while ((dp = readdir(dir)))
	{
		if (flag->a == 0)
			if (dp->d_name[0] == '.')
				continue;
		if (ft_strcmp(dp->d_name, "..") != 0 && ft_strcmp(dp->d_name, ".") != 0)
		{
			if (path_is_dir(set_path(path, buffer, dp->d_name, 1), 0))
				if (new_dir(buffer, n_dir))
					flag->l_r == 1 ? T_DIR_PUSH : T_DIR_PUSH_2;
		}
	}
	closedir(dir);
	return (n_dir);
}

t_ndir			*dir_br(char *path, t_flag *flag, t_ndir *n_dir)
{
	DIR			*dir;
	t_ndir		*tmp;

	tmp = NULL;
	if (n_dir != NULL)
	{
		path = ft_strdup(n_dir->path);
		ft_list_del_node(&n_dir, path);
	}
	if (!(dir = opendir(path)))
	{
		n_dir = another_dir(n_dir, flag, path);
		return (n_dir);
	}
	print_file(path, flag, 1);
	n_dir = another_dir(n_dir, flag, path);
	closedir(dir);
	return (n_dir);
}

void			print_dir(char *path, t_flag *flag, int key)
{
	t_ndir		*dir;

	dir = NULL;
	if (key > 0)
	{
		if (key > 1)
			write(1, "\n", 1);
		ft_putstr(path);
		write(1, ":\n", 2);
	}
	if (flag->b_r == 1)
	{
		dir = dir_br(path, flag, dir);
		while (dir)
		{
			write(1, "\n", 1);
			ft_putstr(dir->path);
			write(1, ":\n", 2);
			dir = dir_br(path, flag, dir);
		}
	}
	else
		flag->l == 1 ? print_file(path, flag, 1) : print_file(path, flag, 0);
}
