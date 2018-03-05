/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/set.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_SET_H
# define LIBFT_DS_SET_H

# include "set.h"

typedef struct	s_set
{
	uint32_t	cap;
	uint32_t	len;
	uint32_t	occupieds;
	uint32_t	upper_bound;
	uint8_t		*bucks;
	t_hasher	hasher;
	size_t		ksz;
	void		*keys;
}				t_set;

extern void		ft_setctor(t_set *set, t_hasher hasher, size_t ksz);
extern void		ft_setdtor(t_set *set, t_dtor kdtor);
extern void		ft_setclr(t_set *set);
extern t_bool	ft_setget(t_set *set, void *k, uint32_t *out);
extern t_bool	ft_setput(t_set *set, void *key, uint32_t *out);
extern size_t	ft_setrsz(t_set *set, uint32_t sz);

#endif
