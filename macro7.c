/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:07:17 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:35:55 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				has_acl(char *path, t_stat *l_stat)
{
	char		res;
	acl_t		acl;

	res = 0;
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl != NULL)
	{
		if (l_stat->st_mode & S_ISVTX)
			write(1, "T", 1);
		else if (l_stat->st_mode & S_IXOTH)
			write(1, "x", 1);
		else
			write(1, "-", 1);
		write(1, "+ ", 2);
		res = 1;
	}
	acl_free(acl);
	return (res);
}

void			print_dir_name(char *path, int len, int i)
{
	while (path[len] != '/')
	{
		len--;
		if (len == 0)
			break ;
	}
	if (len == 0)
		ft_putstr(path);
	else
	{
		while (i < len)
		{
			write(1, &path[i], 1);
			i++;
		}
	}
}

int				get_pos_dir_r(t_ndir *list, char *path, int i)
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

int				*set_cmp(int i, int ac)
{
	int			*tab;

	tab = ft_memalloc(sizeof(int) * 2);
	if (tab)
	{
		tab[0] = 0;
		tab[1] = ac - i;
	}
	return (tab);
}

void			print_stat_n(t_flag *flag, t_stat *status)
{
	if (S_ISCHR(status->st_mode))
		print_mn(status, flag);
	else
	{
		if (MAX_SIZE_MINOR > 0 || MAX_SIZE_MAJOR > 0)
		{
			while (MAX_SIZE_MAJOR_P-- > 0)
				write(1, " ", 1);
			while (MAX_SIZE_MINOR_P-- > 0)
				write(1, " ", 1);
			write(1, "   ", 3);
		}
		ft_printf("%lld ", status->st_size);
	}
	print_time(status);
}
