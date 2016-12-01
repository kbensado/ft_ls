/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 00:45:27 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/08 03:19:57 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_pos_dir(t_ndir *list, char *path, int i)
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
