/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/map.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_MAP_H
# define LIBFT_DS_MAP_H

# include "../str.h"
# include "../hash.h"

# define MAP_HASH_UPPER 0.77

enum			e_bucket
{
	BUCKET_DELETED = 1,
	BUCKET_EMPTY = 2,
	BUCKET_BOTH = BUCKET_DELETED | BUCKET_EMPTY
};

typedef struct	s_map
{
	uint32_t	cap;
	uint32_t	len;
	uint32_t	occupieds;
	uint32_t	upper_bound;
	uint8_t		*bucks;
	t_hasher	hasher;
	size_t		ksz;
	size_t		vsz;
	void		*keys;
	void		*vals;
}				t_map;

extern void		ft_mapctor(t_map *map, t_hasher hasher, size_t ksz, size_t vsz);
extern void		ft_mapdtor(t_map *map, t_dtor kdtor, t_dtor vdtor);
extern void		ft_mapclr(t_map *map);
extern t_bool	ft_mapget(t_map *map, void *k, uint32_t *out);
extern t_bool	ft_mapput(t_map *map, void *key, uint32_t *out);
extern t_bool	ft_mapdel(t_map *map, uint32_t it);
extern size_t	ft_maprsz(t_map *map, uint32_t sz);

#endif
