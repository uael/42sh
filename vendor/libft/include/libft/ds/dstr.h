/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ds/dstr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DS_DSTR_H
# define LIBFT_DS_DSTR_H

# include "../str.h"
# include "../math.h"

# define FT_DSTR_MIN_CAP 32

typedef struct	s_dstr
{
	char		*buf;
	size_t		cap;
	size_t		len;
}				t_dstr;

extern void		ft_dstr_ctor(t_dstr *s);
extern void		ft_dstr_dtor(t_dstr *s, t_dtor idtor);
extern size_t	ft_dstr_size(t_dstr *s);
extern char		*ft_dstr_begin(t_dstr *s);
extern char		*ft_dstr_end(t_dstr *s);
extern char		*ft_dstr_at(t_dstr *s, size_t i);
extern t_bool	ft_dstr_realloc(t_dstr *s, size_t n);
extern t_bool	ft_dstr_grow(t_dstr *s, size_t n);
extern t_bool	ft_dstr_ensure(t_dstr *s, size_t n);
extern char		*ft_dstr_pushn(t_dstr *s, size_t n);
extern char		*ft_dstr_pushnc(t_dstr *s, char const *b, size_t n);
extern char		*ft_dstr_append(t_dstr *s, char const *b);
extern char		*ft_dstr_push(t_dstr *s);
extern char		*ft_dstr_pushc(t_dstr *s, char item);
extern char		*ft_dstr_unshiftn(t_dstr *s, size_t n);
extern char		*ft_dstr_unshiftnc(t_dstr *s, char const *b, size_t n);
extern char		*ft_dstr_prepend(t_dstr *s, char const *b);
extern char		*ft_dstr_unshift(t_dstr *s);
extern char		*ft_dstr_unshiftc(t_dstr *s, char item);
extern char		*ft_dstr_putn(t_dstr *s, size_t i, size_t n);
extern char		*ft_dstr_putnc(t_dstr *s, size_t i, char const *b, size_t n);
extern char		*ft_dstr_emplace(t_dstr *s, size_t i, char const *b);
extern char		*ft_dstr_put(t_dstr *s, size_t i);
extern char		*ft_dstr_putc(t_dstr *s, size_t i, char item);
extern size_t	ft_dstr_popn(t_dstr *s, size_t n, char *out);
extern t_bool	ft_dstr_pop(t_dstr *s, char *out);
extern size_t	ft_dstr_shiftn(t_dstr *s, size_t n, char *out);
extern t_bool	ft_dstr_shift(t_dstr *s, char *out);
extern size_t	ft_dstr_removen(t_dstr *s, size_t i, size_t n, char *out);
extern t_bool	ft_dstr_remove(t_dstr *s, size_t i, char *out);

#endif
