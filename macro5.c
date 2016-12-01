/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 12:57:04 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/08 02:34:00 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_blank(t_flag *flag, t_stat *status, char *path)
{
	MAX_SIZE_LINK_P = MAX_SIZE_LINK - ft_nbr_len(status->st_nlink);
	MAX_NAME_P = MAX_NAME - ft_strlen(path);
	MAX_SIZE_P = MAX_SIZE - ft_nbr_len(status->st_size);
	MAX_LEN_GROUP_P = MAX_LEN_GROUP - get_len_group(status);
	MAX_LEN_OWN_P = MAX_LEN_OWN - get_len_own(status);
	MAX_SIZE_MAJOR_P = MAX_SIZE_MAJOR - ft_nbr_len(major(status->st_rdev));
	MAX_SIZE_MINOR_P = MAX_SIZE_MINOR - ft_nbr_len(minor(status->st_rdev));
}

void	print_block(char *name, t_flag *flag, char *path)
{
	char		*buffer;
	t_stat		status;

	buffer = ft_strnew(BUFF_SIZE);
	set_path(name, buffer, path, 1);
	if (lstat(buffer, &status) == 0)
		BLOCK_SIZE_FILE_P = BLOCK_SIZE_FILE - ft_nbr_len(status.st_blocks);
	while (BLOCK_SIZE_FILE_P-- > 0)
		write(1, " ", 1);
	buffer = ft_strnew(BUFF_SIZE);
	if (buffer)
	{
		set_path(name, buffer, path, 1);
		if (lstat(buffer, &status) == 0)
			PRINT("%d ", status.st_blocks);
	}
	ft_strdel(&buffer);
}

void	get_block_dir(t_tree *tree, char *path)
{
	char		*buffer;
	t_stat		status;
	long long	res;

	res = 0;
	buffer = ft_strnew(BUFF_SIZE);
	if (buffer)
	{
		if (tree)
		{
			while (tree)
			{
				set_path(path, buffer, tree->path, 1);
				if (lstat(buffer, &status) == 0)
					res += status.st_blocks;
				tree = tree->next;
			}
			PRINT("total %d\n", res);
		}
	}
	ft_strdel(&buffer);
}

int		list_size(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree)
	{
		i++;
		tree = tree->next;
	}
	return (i);
}

void	get_name(char *path, int i, t_flag *flag, char *name)
{
	int	len;

	len = ft_strlen(path) - 1;
	while (path[len] != '/')
	{
		if (len == 0)
			break ;
		len--;
	}
	if (len != 0)
		i = len + 1;
	else
		i = len;
	while (path[i])
	{
		write(1, &path[i], 1);
		i++;
	}
	if (flag && flag->b_f == 1)
		write_f(path, name);
	write(1, "\n", 1);
}
