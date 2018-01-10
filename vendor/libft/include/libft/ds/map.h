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

#define MAP_HASH_UPPER 0.77

enum			e_bucket
{
	BUCKET_DELETED = 1,
	BUCKET_EMPTY = 2,
	BUCKET_BOTH = BUCKET_DELETED | BUCKET_EMPTY
};

#define BUCKET_ISEMPTY(buckets, i) (((buckets)[i]&BUCKET_EMPTY)==BUCKET_EMPTY)
#define BUCKET_ISDEL(buckets, i) (((buckets)[i]&BUCKET_DELETED)==BUCKET_DELETED)
#define BUCKET_ISEITHER(buckets, i) (((buckets)[i]&BUCKET_BOTH)!=0)
#define BUCKET_ISPOPULATED(buckets, i) (((buckets)[i]&BUCKET_BOTH)==0)
#define BUCKET_SET_ISDEL_FALSE(buckets, i) ((buckets)[i]&=~BUCKET_DELETED)
#define BUCKET_SET_ISEMPTY_FALSE(buckets, i) ((buckets)[i]&=~BUCKET_EMPTY)
#define BUCKET_SET_ISBOTH_FALSE(buckets, i) ((buckets)[i]=0)
#define BUCKET_SET_ISDEL_TRUE(buckets, i) ((buckets)[i]|=BUCKET_DELETED)

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
extern t_bool	ft_mapget(t_map *map, void *key, uint32_t *out);
extern t_bool	ft_mapput(t_map *map, void *key, uint32_t *out);
extern size_t	ft_mapresize(t_map *map, uint32_t sz);

#endif
