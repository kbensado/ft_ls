/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:02:57 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/09 16:44:44 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			write_f(char *path, char *name)
{
	char		*buffer;
	t_stat		status;

	buffer = ft_strnew(BUFF_SIZE);
	set_path(name, buffer, path, 1);
	if (lstat(buffer, &status) == 0)
	{
		if (S_ISDIR(status.st_mode))
			ft_putchar('/');
		else if (S_ISLNK(status.st_mode))
			ft_putchar('@');
		else if (S_ISSOCK(status.st_mode))
			ft_putchar('=');
		else if (S_ISFIFO(status.st_mode))
			ft_putchar('|');
		else if (S_ISWHT(status.st_mode))
			ft_putchar('%');
		else if (status.st_mode & S_IXUSR)
			ft_putchar('*');
	}
	ft_strdel(&buffer);
}

int				get_len_own(t_stat *stat)
{
	t_pass		*pass;

	if (!(pass = getpwuid(stat->st_uid)))
	{
		perror("ls");
		return (0);
	}
	return (ft_strlen(pass->pw_name));
}

int				get_len_group(t_stat *stat)
{
	t_group		*grp;

	if (!(grp = getgrgid(stat->st_gid)))
	{
		perror("ls");
		return (0);
	}
	return (ft_strlen(grp->gr_name));
}

void			print_mn(t_stat *status, t_flag *flag)
{
	while (MAX_SIZE_MAJOR_P-- > 0)
		write(1, " ", 1);
	ft_putnbr(major(status->st_rdev));
	write(1, ", ", 2);
	while (MAX_SIZE_MINOR_P-- > 0)
		write(1, " ", 1);
	ft_putnbr(minor(status->st_rdev));
	write(1, " ", 1);
}

void			print_privilege_ext(struct stat *l_stat, char *path)
{
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
	{
		if (l_stat->st_mode & S_IXOTH)
			write(1, "x", 1);
		else if (l_stat->st_mode & S_ISVTX)
			write(1, "T", 1);
		else
			write(1, "-", 1);
		write(1, "@ ", 2);
		return ;
	}
	if (has_acl(path, l_stat))
		return ;
	if (l_stat->st_mode & S_ISVTX)
		write(1, "t  ", 3);
	else if (l_stat->st_mode & S_IXOTH)
		write(1, "x  ", 3);
	else
		write(1, "-  ", 3);
}
