/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:34:24 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:47:41 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_privilege(struct stat *l_stat, char *path)
{
	l_stat->st_mode & S_IRUSR ? write(1, "r", 1) : write(1, "-", 1);
	l_stat->st_mode & S_IWUSR ? write(1, "w", 1) : write(1, "-", 1);
	if (l_stat->st_mode & S_IXUSR)
		write(1, "x", 1);
	else if (l_stat->st_mode & S_ISUID)
		write(1, "S", 1);
	else
		write(1, "-", 1);
	l_stat->st_mode & S_IRGRP ? write(1, "r", 1) : write(1, "-", 1);
	l_stat->st_mode & S_IWGRP ? write(1, "w", 1) : write(1, "-", 1);
	if (l_stat->st_mode & S_IXGRP)
		write(1, "x", 1);
	else if (l_stat->st_mode & S_ISGID)
		write(1, "S", 1);
	else
		write(1, "-", 1);
	l_stat->st_mode & S_IROTH ? write(1, "r", 1) : write(1, "-", 1);
	l_stat->st_mode & S_IWOTH ? write(1, "w", 1) : write(1, "-", 1);
	print_privilege_ext(l_stat, path);
}

void			print_attr(struct stat *l_stat, t_flag *list)
{
	if (list->l == 1)
	{
		if (S_ISDIR(l_stat->st_mode))
			ft_putchar('d');
		else if (S_ISREG(l_stat->st_mode))
			ft_putchar('-');
		else if (S_ISLNK(l_stat->st_mode))
			ft_putchar('l');
		else if (S_ISBLK(l_stat->st_mode))
			ft_putchar('b');
		else if (S_ISCHR(l_stat->st_mode))
			ft_putchar('c');
		else if (S_ISSOCK(l_stat->st_mode))
			ft_putchar('s');
	}
}

void			print_stat(char *path, t_flag *flag, char *name)
{
	t_stat		status;

	if (lstat(path, &status) == 0)
	{
		print_attr(&status, flag);
		print_privilege(&status, path);
		set_blank(flag, &status, name);
		while (MAX_SIZE_LINK_P-- > 0)
			write(1, " ", 1);
		ft_putnbr(status.st_nlink);
		write(1, " ", 1);
		print_own(&status, flag, path);
		print_group(&status, flag);
		while (MAX_SIZE_P-- > 0)
			write(1, " ", 1);
		print_stat_n(flag, &status);
	}
}

void			print_link(char *path)
{
	t_stat		l_stat;
	char		*buff;

	buff = NULL;
	if (lstat(path, &l_stat) == 0)
	{
		buff = ft_strnew(l_stat.st_size + 1);
		if (readlink(path, buff, l_stat.st_size + 1))
		{
			buff[l_stat.st_size + 1] = '\0';
			write(1, " -> ", 4);
			ft_putstr(buff);
			ft_strdel(&buff);
		}
	}
}

void			print_with_filter(char *path, t_flag *flag, char *name, int key)
{
	char		*buffer;

	buffer = ft_strnew(BUFF_SIZE);
	if (flag->l_s == 1)
		print_block(name, flag, path);
	if (flag->l == 1)
	{
		if (key == 1)
			set_path(name, buffer, path, 1);
		else
			buffer = ft_strcpy(buffer, path);
		print_stat(buffer, flag, path);
		ft_putstr(path);
		if (flag->b_f == 1)
			write_f(path, name);
		if (path_is_syml(buffer))
			print_link(buffer);
		write(1, "\n", 1);
	}
	else
		WS(path);
	ft_strdel(&buffer);
}
