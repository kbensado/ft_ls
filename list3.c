/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 15:40:46 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/08 02:37:52 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				get_pos_dir(t_ndir *list, char *path, int i)
{
	while (list)
	{
		if (ft_strcmp(path, list->path) < 0)
			return (i);
		i++;
		list = list->next;
	}
	return (i);
}

t_ndir			*ft_create_elem_dir(char *path)
{
	t_ndir		*ndir;

	if (!(ndir = (t_ndir *)malloc(sizeof(t_ndir))))
		return (NULL);
	ft_bzero(ndir, sizeof(t_ndir));
	ndir->path = ft_strdup(path);
	ndir->size = 0;
	ndir->time = 0;
	ndir->next = NULL;
	return (ndir);
}

void			ft_list_del_node(t_ndir **begin_list, char *path)
{
	t_ndir		*list;

	if (*begin_list)
	{
		if (ft_strcmp((*begin_list)->path, path) == 0)
		{
			list = *begin_list;
			ft_strdel(&list->path);
			*begin_list = (*begin_list)->next;
			free(list);
			ft_list_del_node(begin_list, path);
		}
		else
			ft_list_del_node(&(*begin_list)->next, path);
	}
}

static void		list_push_dir(t_ndir **begin_list, char *name,
				t_ndir *tmp, t_ndir *list)
{
	if (begin_list == NULL)
	{
		tmp->next = ft_create_elem_dir(name);
		tmp->next->next = list;
		return ;
	}
	tmp = *begin_list;
	*begin_list = ft_create_elem_dir(name);
	list = *begin_list;
	list->next = tmp;
}

void			ft_list_push_dir(t_ndir **begin_list, char *name,
				t_ndir *tmp, int i)
{
	t_ndir	*list;

	list = *begin_list;
	if (list)
	{
		if (i == 0)
		{
			list_push_dir(begin_list, name, tmp, list);
			return ;
		}
		while (i)
		{
			if (i-- == 1)
				tmp = list;
			list = list->next;
		}
		if (list)
			list_push_dir(NULL, name, tmp, list);
		else
			tmp->next = ft_create_elem_dir(name);
	}
	else
		*begin_list = ft_create_elem_dir(name);
}
