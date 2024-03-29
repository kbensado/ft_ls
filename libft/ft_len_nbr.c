/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:11:16 by kbensado          #+#    #+#             */
/*   Updated: 2016/11/11 07:10:45 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_nbr_len(long nb)
{
	int		i;

	i = 0;
	if (nb < 10)
		return (1);
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
