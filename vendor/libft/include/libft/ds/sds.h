/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/sds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_SDS_H
# define LIBFT_DS_SDS_H

# include "../str.h"
# include "../math.h"

# define FT_SDS_MIN_CAP 32

typedef struct	s_sds
{
	char		*buf;
	size_t		cap;
	size_t		len;
}				t_sds;

extern void		ft_sdsctor(t_sds *s);
extern void		ft_sdsdtor(t_sds *s);
extern size_t	ft_sdslen(t_sds *s);
extern char		*ft_sdsbeg(t_sds *s);
extern char		*ft_sdsend(t_sds *s);
extern char		*ft_sdsback(t_sds *self);
extern char		*ft_sdsat(t_sds *s, size_t i);
extern size_t	ft_sdsalloc(t_sds *s, size_t n);
extern size_t	ft_sdsgrow(t_sds *s, size_t n);
extern size_t	ft_sdsaver(t_sds *s, size_t n);
extern char		*ft_sdsnpush(t_sds *s, size_t n);
extern char		*ft_sdsmpush(t_sds *s, char const *b, size_t n);
extern char		*ft_sdsapd(t_sds *s, char const *b);
extern char		*ft_sdspush(t_sds *s);
extern char		*ft_sdscpush(t_sds *s, char item);
extern char		*ft_sdsnusht(t_sds *s, size_t n);
extern char		*ft_sdsmusht(t_sds *s, char const *b, size_t n);
extern char		*ft_sdsprd(t_sds *s, char const *b);
extern char		*ft_sdsusht(t_sds *s);
extern char		*ft_sdscusht(t_sds *s, char item);
extern char		*ft_sdsnput(t_sds *s, size_t i, size_t n);
extern char		*ft_sdsmput(t_sds *s, size_t idx, char const *buf, size_t n);
extern char		*ft_sdsemp(t_sds *s, size_t i, char const *b);
extern char		*ft_sdsput(t_sds *s, size_t i);
extern char		*ft_sdscput(t_sds *s, size_t i, char item);
extern size_t	ft_sdsnpop(t_sds *s, size_t n, char *out);
extern t_bool	ft_sdspop(t_sds *s, char *out);
extern size_t	ft_sdsnsht(t_sds *s, size_t n, char *out);
extern t_bool	ft_sdssht(t_sds *s, char *out);
extern size_t	ft_sdsnrem(t_sds *s, size_t i, size_t n, char *out);
extern t_bool	ft_sdsrem(t_sds *s, size_t i, char *out);

#endif
