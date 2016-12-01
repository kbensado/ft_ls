/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 10:47:34 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:43:40 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			open_fail(char *path, t_flag *flag)
{
	t_stat		status;

	if (lstat(path, &status) < 0)
	{
		ft_error(path, 1);
		return ;
	}
	print_with_filter(path, flag, "", 0);
	return ;
}

static void		error_name(char *path, int i)
{
	int	len;

	len = ft_strlen(path) - 1;
	while (path[len] != '/')\
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
		write(2, &path[i], 1);
		i++;
	}
}

int				ft_error(char *str, int flag)
{
	if (flag == 1)
	{
		write(2, "ls: ", 4);
		error_name(str, 0);
		write(2, ": ", 2);
		perror("");
		return (0);
	}
	else
	{
		write(2, "ls: illegal option -- ", 22);
		write(2, &str[0], 1);
		write(2, "\nusage: ls [-FRSalrst] [file ...]\n", 35);
		return (0);
	}
	return (0);
}
