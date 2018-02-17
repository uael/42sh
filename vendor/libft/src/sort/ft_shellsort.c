/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort/ft_shellsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 23:16:44 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/13 01:14:30 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_shellsort - generic array sort
*/

#include "libft.h"

void		ft_shellsort(void *arr, size_t length, size_t n, t_ncmp *cmp)
{
	const size_t	gaps[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0 };
	t_uchar			swap[n];
	size_t			i;
	int				j;
	int				ngap;

	ngap = -1;
	while ((i = gaps[++ngap]))
		while (i < length)
		{
			ft_memcpy(swap, ((t_uchar *)arr) + (i * n), n);
			j = (int)i - (int)gaps[ngap];
			while (j >= 0 \
					&& cmp(((t_uchar *)arr) + ((size_t)j * n), swap, n) > 0)
			{
				ft_memcpy(((t_uchar *)arr) + (((size_t)j + gaps[ngap]) * n), \
							((t_uchar *)arr) + ((size_t)j * n), n);
				j -= (int)gaps[ngap];
			}
			ft_memcpy(((t_uchar *)arr) + (((size_t)j + gaps[ngap]) * n), \
						swap, n);
			i++;
		}
}
