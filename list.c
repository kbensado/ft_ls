/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 17:32:31 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/08 02:14:39 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree			*ft_create_elem(char *path)
{
	t_tree		*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	ft_bzero(tree, sizeof(t_tree));
	tree->path = ft_strdup(path);
	tree->size = 0;
	tree->time = 0;
	tree->next = NULL;
	return (tree);
}

int				get_pos(t_tree *list, char *path, int i)
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

void			ft_list_clear(t_tree **begin_list)
{
	t_tree		*list;
	t_tree		*temp;

	if (*begin_list == NULL)
		return ;
	list = *begin_list;
	while (list)
	{
		ft_strdel(&list->path);
		temp = list->next;
		free(list);
		list = temp;
	}
	*begin_list = NULL;
}

static void		list_push(t_tree **begin_list, char *name,
				t_tree *tmp, t_tree *list)
{
	if (begin_list == NULL)
	{
		tmp->next = ft_create_elem(name);
		tmp->next->next = list;
		return ;
	}
	tmp = *begin_list;
	*begin_list = ft_create_elem(name);
	list = *begin_list;
	list->next = tmp;
}

void			ft_list_push(t_tree **begin_list, char *name,
				t_tree *tmp, int i)
{
	t_tree	*list;

	list = *begin_list;
	if (list)
	{
		if (i == 0)
		{
			list_push(begin_list, name, tmp, list);
			return ;
		}
		while (i)
		{
			if (i-- == 1)
				tmp = list;
			list = list->next;
		}
		if (list)
			list_push(NULL, name, tmp, list);
		else
			tmp->next = ft_create_elem(name);
	}
	else
		*begin_list = ft_create_elem(name);
}
