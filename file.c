/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 18:28:01 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/11 00:30:59 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_list(t_tree *tree)
{
	while (tree)
	{
		WS(tree->path);
		tree = tree->next;
	}
}

t_tree		*fill_list(char *path, char *name, t_tree *tree, t_flag *flag)
{
	char	*buffer;
	t_stat	status;

	if (tree == NULL)
	{
		ft_list_push(&tree, name, NULL, get_pos(tree, name, 0));
		return (tree);
	}
	buffer = ft_strnew(BUFF_SIZE);
	if (lstat(path, &status) == 0)
	{
		if (flag->t == 0 && flag->b_s == 0)
			flag->l_r == 1 ? LIST_FILE_P : LIST_FILE_P_2;
		else if (flag->b_s == 1)
			flag->l_r == 1 ? LIST_FILE_S : LIST_FILE_S_2;
		else if (flag->t == 1)
			flag->l_r == 1 ? LIST_FILE_T : LIST_FILE_T_2;
		ft_strdel(&buffer);
		return (tree);
	}
	return (tree);
}

t_tree		*fill_file(char *path, t_flag *flag, t_tree *tree)
{
	t_dir	*dp;
	DIR		*dir;

	if (!(dir = opendir(path)))
	{
		ft_error(path, 1);
		return (NULL);
	}
	while ((dp = readdir(dir)))
	{
		if (flag->a == 0 && dp->d_name[0] == '.')
			continue ;
		tree = fill_list(path, dp->d_name, tree, flag);
	}
	closedir(dir);
	return (tree);
}

char		**sort_tab(char **tab, t_flag *flag)
{
	if (flag->l_r == 0)
		sort_ascii(tab, flag);
	return (tab);
}

void		print_file(char *path, t_flag *flag, int key)
{
	t_tree	*tree;
	char	*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	tree = NULL;
	clean_stat(flag);
	get_stat_of_file(path, flag, buffer, NULL);
	tree = fill_file(path, flag, tree);
	if (flag->l == 1 && key == 1)
		get_block_dir(tree, path);
	while (tree)
	{
		print_with_filter(tree->path, flag, path, 1);
		tree = tree->next;
	}
	ft_list_clear(&tree);
	ft_strdel(&buffer);
}
