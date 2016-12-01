/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:41:18 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/11 00:30:34 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			clean_stat(t_flag *flag)
{
	NB_FILE = 0;
	MAX_NAME = 0;
	MAX_SIZE = 0;
	MAX_LEN_OWN = 0;
	MAX_LEN_GROUP = 0;
	MAX_SIZE_MAJOR = 0;
	MAX_SIZE_MINOR = 0;
	MAX_SIZE_LINK = 0;
	BLOCK_SIZE_LEN = 0;
	BLOCK_SIZE_FILE = 0;
}

int				ft_strcmpl(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	if (s1 != '\0' && s2[i] == '\0')
	{
		return (-1);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void			print_own(t_stat *stat, t_flag *flag, char *path)
{
	t_pass		*pass;

	if (!(pass = getpwuid(stat->st_uid)))
	{
		ft_error(path, 1);
		return ;
	}
	write(1, pass->pw_name, ft_strlen(pass->pw_name));
	while (MAX_LEN_OWN_P-- > 0)
		write(1, " ", 1);
	write(1, "  ", 2);
}

long			get_time(char *path)
{
	t_stat		stat;

	if (lstat(path, &stat) == 0)
		return (stat.st_mtimespec.tv_sec);
	return (0);
}

int				path_is_file(char *path)
{
	t_stat		stat;

	if (lstat(path, &stat) == 0)
	{
		if (S_ISREG(stat.st_mode))
			return (1);
		else
			return (0);
	}
	return (0);
}
