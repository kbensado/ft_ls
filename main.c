/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 11:09:59 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/12 00:45:39 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		no_arg(char **av)
{
	int			i;

	i = 1;
	if (av[1] == NULL)
		return (1);
	while (av[i])
	{
		if (av[i][0] == '-')
			i++;
		else
			return (0);
	}
	return (1);
}

int				arg_start(char **av)
{
	int			i;

	i = 1;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 1 && av[i][0] == '-')
			i++;
		else
			break ;
	}
	return (i);
}

char			**get_arg(char **av, int start, int i, int j)
{
	char		**res;
	int			tmp;
	t_stat		stat;

	tmp = i;
	res = ft_memalloc(sizeof(char *) * (i - start));
	if (res == NULL)
		return (NULL);
	ft_bzero(res, (sizeof(char *) * (i - start)));
	while (--i >= start)
	{
		if (lstat(av[i], &stat) != 0)
		{
			res[j] = ft_strdup(av[i]);
			j++;
		}
	}
	i = tmp;
	while (start < i)
	{
		if (lstat(av[start], &stat) == 0)
			res[j++] = ft_strdup(av[start]);
		start++;
	}
	return (res);
}

char			**first_check(char **av)
{
	char		**arg;
	int			i;
	int			start;

	i = arg_start(av);
	start = i;
	arg = NULL;
	while (av[i])
		i++;
	if (start < i)
		arg = get_arg(av, start, i, 0);
	else
		arg = get_arg(av, i, start, 0);
	return (arg);
}

int				main(int ac, char **av, char **env)
{
	t_flag		flag;
	char		**arg;
	int			i;
	int			*cmp;

	(void)ac;
	ft_bzero(&flag, sizeof(t_flag));
	if (!(arg = first_check(av)))
		return (0);
	i = get_flag(&flag, av, 1, env);
	cmp = set_cmp(i, ac);
	if (no_arg(av))
		set_file(arg, cmp, &flag, 1);
	else
		set_file(arg, cmp, &flag, 0);
	return (0);
}
