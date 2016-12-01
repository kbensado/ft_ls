/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:40:55 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/09 15:31:50 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			set_stat(t_dir *dp, t_stat *status, t_flag *flag)
{
	if (S_ISCHR(status->st_mode))
	{
		if (MAX_SIZE_MAJOR < ft_nbr_len(major(status->st_rdev)))
			MAX_SIZE_MAJOR = ft_nbr_len(major(status->st_rdev));
		if (MAX_SIZE_MINOR < ft_nbr_len(minor(status->st_rdev)))
			MAX_SIZE_MINOR = ft_nbr_len(minor(status->st_rdev));
	}
	if (ft_strlen(dp->d_name) > (size_t)MAX_NAME)
		MAX_NAME = ft_strlen(dp->d_name);
	if (MAX_SIZE < ft_nbr_len(status->st_size))
		MAX_SIZE = ft_nbr_len(status->st_size);
	if (get_len_own(status) > MAX_LEN_OWN)
		MAX_LEN_OWN = get_len_own(status);
	if (get_len_own(status) > MAX_LEN_GROUP)
		MAX_LEN_GROUP = get_len_group(status);
	if (MAX_SIZE_LINK < ft_nbr_len(status->st_nlink))
		MAX_SIZE_LINK = ft_nbr_len(status->st_nlink);
	if (BLOCK_SIZE_FILE < ft_nbr_len(status->st_blocks))
		BLOCK_SIZE_FILE = ft_nbr_len(status->st_blocks);
}

int				time_cmp(unsigned long t11, unsigned long t12,
						unsigned long t21, unsigned long t22)
{
	if (t11 == t21)
	{
		if (t12 > t22)
			return (1);
		else
			return (0);
	}
	if (t11 > t21)
		return (1);
	return (0);
}

void			print_time(t_stat *status)
{
	char			*mtime;
	int				j;
	unsigned int	now;

	j = 4;
	now = time(NULL);
	if (((now - status->st_mtime) <= -1)
		|| (now - (status->st_mtime) > 15811200))
	{
		mtime = ctime(&status->st_mtime);
		while (j < 10)
			ft_putchar(mtime[j++]);
		j = 19;
		ft_putchar(' ');
		while (j < 24)
			ft_putchar(mtime[j++]);
	}
	else
	{
		mtime = ctime(&status->st_mtime);
		while (j < 16)
			ft_putchar(mtime[j++]);
	}
	ft_putchar(' ');
}

void			print_group(t_stat *stat, t_flag *flag)
{
	t_group		*grp;

	if (!(grp = getgrgid(stat->st_gid)))
	{
		perror("ls");
		return ;
	}
	write(1, grp->gr_name, ft_strlen(grp->gr_name));
	while (MAX_LEN_GROUP_P-- > 0)
		write(1, " ", 1);
	write(1, "  ", 2);
}

char			*set_path(char *path, char *buffer, char *name, int flag)
{
	if (flag == 1)
	{
		ft_bzero(buffer, BUFF_SIZE);
		ft_strcat(buffer, path);
		ft_strcat(buffer, "/");
		ft_strcat(buffer, name);
		return (buffer);
	}
	ft_bzero(buffer, BUFF_SIZE);
	ft_strcat(buffer, path);
	ft_strcat(buffer, name);
	return (buffer);
}
