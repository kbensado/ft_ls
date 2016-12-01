/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 15:56:33 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/08 02:21:37 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_pos_time(t_tree *list, char *path, int i, char *root)
{
	t_stat		stat;
	t_stat		stat2;
	char		*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	if (LSTAT_1)
	{
		while (list)
		{
			if (LSTAT_1)
			{
				if (LSTAT_TIME)
				{
					ft_strdel(&buffer);
					return (i);
				}
			}
			i++;
			list = list->next;
		}
		return (i);
	}
	ft_strdel(&buffer);
	return (i);
}

int		get_pos_size(t_tree *list, char *path, int i, char *root)
{
	t_stat		stat;
	t_stat		stat2;
	char		*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	if (LSTAT_1)
	{
		while (list)
		{
			if (LSTAT_1)
			{
				if (stat.st_size > stat2.st_size)
				{
					ft_strdel(&buffer);
					return (i);
				}
			}
			i++;
			list = list->next;
		}
		return (i);
	}
	ft_strdel(&buffer);
	return (i);
}

int		get_pos_r(t_tree *list, char *path, int i)
{
	while (list)
	{
		if (ft_strcmp(path, list->path) > 0)
			return (i);
		i++;
		list = list->next;
	}
	return (i);
}

int		get_pos_time_r(t_tree *list, char *path, int i, char *root)
{
	t_stat		stat;
	t_stat		stat2;
	char		*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	if (LSTAT_1)
	{
		while (list)
		{
			if (LSTAT_1)
			{
				if (!(LSTAT_TIME))
				{
					ft_strdel(&buffer);
					return (i);
				}
			}
			i++;
			list = list->next;
		}
		return (i);
	}
	ft_strdel(&buffer);
	return (i);
}

int		get_pos_size_r(t_tree *list, char *path, int i, char *root)
{
	t_stat		stat;
	t_stat		stat2;
	char		*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	if (LSTAT_1)
	{
		while (list)
		{
			if (LSTAT_1)
			{
				if (stat.st_size < stat2.st_size)
				{
					ft_strdel(&buffer);
					return (i);
				}
			}
			i++;
			list = list->next;
		}
		return (i);
	}
	ft_strdel(&buffer);
	return (i);
}
