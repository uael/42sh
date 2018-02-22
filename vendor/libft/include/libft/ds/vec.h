/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/vec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 11:32:22 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_VEC_H
# define LIBFT_DS_VEC_H

# include "../ex.h"
# include "../mem.h"
# include "../str.h"
# include "../math.h"

# define FT_VEC_MIN_CAP 32

typedef struct	s_vec
{
	void		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
}				t_vec;

extern void		ft_vecctor(t_vec *s, size_t isz);
extern void		ft_vecdtor(t_vec *s, t_dtor i);
extern void		ft_vecmdtor(t_vec *s, t_dtor i);
extern void		ft_vecclr(t_vec *s, t_dtor i);
extern size_t	ft_vecclean(t_vec *self, size_t n, t_dtor idtor);
extern size_t	ft_veclen(t_vec *s);
extern void		*ft_vecbeg(t_vec *s);
extern void		*ft_vecend(t_vec *s);
extern void		*ft_vecback(t_vec *s);
extern void		*ft_vecat(t_vec *s, size_t i);
extern size_t	ft_vecalloc(t_vec *s, size_t n);
extern size_t	ft_vecgrow(t_vec *s, size_t n);
extern size_t	ft_vecaver(t_vec *s, size_t n);
extern void		*ft_vecnpush(t_vec *s, size_t n);
extern void		*ft_vecmpush(t_vec *s, void const *b, size_t n);
extern void		*ft_vecpush(t_vec *s);
extern void		*ft_veccpush(t_vec *s, void *item);
extern void		*ft_vecnusht(t_vec *s, size_t n);
extern void		*ft_vecmusht(t_vec *s, void const *b, size_t n);
extern void		*ft_vecusht(t_vec *s);
extern void		*ft_veccusht(t_vec *s, void *item);
extern void		*ft_vecnput(t_vec *s, size_t i, size_t n);
extern void		*ft_vecmput(t_vec *self, size_t idx, void const *buf, size_t n);
extern void		*ft_vecput(t_vec *s, size_t i);
extern void		*ft_veccput(t_vec *s, size_t i, void *item);
extern size_t	ft_vecnpop(t_vec *s, size_t n, void *out);
extern t_bool	ft_vecpop(t_vec *s, void *out);
extern size_t	ft_vecnsht(t_vec *s, size_t n, void *out);
extern t_bool	ft_vecsht(t_vec *s, void *out);
extern size_t	ft_vecnrem(t_vec *s, size_t i, size_t n, void *out);
extern t_bool	ft_vecrem(t_vec *s, size_t i, void *out);

#endif
