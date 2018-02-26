/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/deq.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 08:13:57 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_DEQ_H
# define LIBFT_DS_DEQ_H

# include "../ex.h"
# include "../mem.h"
# include "../str.h"
# include "../math.h"

# define FT_DEQ_MIN_CAP 32

typedef struct	s_deq
{
	void		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
	size_t		cur;
}				t_deq;

extern void		ft_deqctor(t_deq *s, size_t isz);
extern void		ft_deqdtor(t_deq *s, t_dtor idtor);
extern void		ft_deqmdtor(t_deq *s, t_dtor idtor);
extern void		ft_deqclr(t_deq *s, t_dtor idtor);
extern size_t	ft_deqclean(t_deq *s, t_dtor idtor);
extern size_t	ft_deqlen(t_deq *s);
extern void		*ft_deqbeg(t_deq *s);
extern void		*ft_deqend(t_deq *s);
extern void		*ft_deqat(t_deq *s, size_t i);
extern size_t	ft_deqalloc(t_deq *s, size_t n);
extern size_t	ft_deqgrow(t_deq *s, size_t n);
extern size_t	ft_deqaver(t_deq *s, size_t n);
extern void		*ft_deqnpush(t_deq *s, size_t n);
extern void		*ft_deqmpush(t_deq *s, void const *b, size_t n);
extern void		*ft_deqpush(t_deq *s);
extern void		*ft_deqcpush(t_deq *s, void *item);
extern void		*ft_deqnusht(t_deq *s, size_t n);
extern void		*ft_deqmusht(t_deq *s, void const *b, size_t n);
extern void		*ft_dequsht(t_deq *s);
extern void		*ft_deqcusht(t_deq *s, void *item);
extern void		*ft_deqnput(t_deq *s, size_t i, size_t n);
extern void		*ft_deqmput(t_deq *self, size_t idx, void const *buf, size_t n);
extern void		*ft_deqput(t_deq *s, size_t i);
extern void		*ft_deqcput(t_deq *s, size_t i, void *item);
extern size_t	ft_deqnpop(t_deq *s, size_t n, void *out);
extern t_bool	ft_deqpop(t_deq *s, void *out);
extern size_t	ft_deqnsht(t_deq *s, size_t n, void *out);
extern t_bool	ft_deqsht(t_deq *s, void *out);
extern size_t	ft_deqnrem(t_deq *s, size_t i, size_t n, void *out);
extern t_bool	ft_deqrem(t_deq *s, size_t i, void *out);

#endif
