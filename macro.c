/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 21:04:33 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:48:34 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			get_stat_of_file(char *path, t_flag *flag,
				char *buffer, DIR *dir)
{
	t_dir		*dp;
	t_stat		status;

	if (!(dir = opendir(path)))
	{
		ft_error(path, 1);
		return ;
	}
	while ((dp = readdir(dir)))
	{
		buffer = set_path(path, buffer, dp->d_name, 1);
		if (lstat(buffer, &status) == 0 && ++NB_FILE)
		{
			if (flag->a == 0 && dp->d_name[0] == '.')
			{
				NB_FILE--;
				continue ;
			}
			set_stat(dp, &status, flag);
		}
	}
	closedir(dir);
}

int				path_is_fifo(char *path)
{
	t_stat		stat;

	if (lstat(path, &stat) == 0)
	{
		if (stat.st_mode & S_IFIFO)
			return (1);
		else
			return (0);
	}
	return (0);
}

int				path_is_dir(char *path, int i)
{
	t_stat		l_stat;

	if (i == 0 && lstat(path, &l_stat) == 0)
	{
		if (S_ISDIR(l_stat.st_mode))
			return (1);
		else
			return (0);
	}
	else
	{
		if (stat(path, &l_stat) == 1)
		{
			if (S_ISDIR(l_stat.st_mode))
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

char			**set_buffer(char *path, size_t i, int j, int len)
{
	t_dir		*dp;
	DIR			*dir;
	char		**buff;

	i = 0;
	if (!(dir = opendir(path)))
	{
		ft_error(path, 1);
		return (NULL);
	}
	if (!(buff = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	while ((dp = readdir(dir)))
	{
		if (ft_strlen(dp->d_name) > i)
			i = ft_strlen(dp->d_name);
	}
	while (j < len)
	{
		buff[j] = ft_strnew(i);
		j++;
	}
	closedir(dir);
	return (buff);
}

int				number_of_dir(DIR *fd, t_flag *flag)
{
	t_stat		l_stat;
	t_dir		*cur_dir;
	int			i;

	i = 0;
	while ((cur_dir = readdir(fd)) != NULL)
	{
		if (l_stat.st_mode & S_IFDIR)
		{
			if (flag->a == 0 && cur_dir->d_name[0] == '.')
				i--;
			i++;
		}
	}
	return (i);
}
