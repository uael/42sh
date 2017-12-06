/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/omstream.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 11:24:33 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_OMSTREAM_H
# define LIBFT_IO_OMSTREAM_H

# include "../ds.h"
# include "ofstream.h"

typedef t_du8	t_omstream;

extern void		ft_omstream_open(t_omstream *self);
extern void		ft_omstream_close(t_omstream *self);
extern t_sz		ft_omstream_write(t_omstream *s, char const *sr, size_t l);
extern t_sz		ft_omstream_writef(t_omstream *self, char const *fmt, ...);
extern t_sz		ft_omstream_vwritef(t_omstream *self, char const *f, va_list a);
extern t_sz		ft_omstream_puts(t_omstream *self, char const *str);
extern t_sz		ft_omstream_putl(t_omstream *self, char const *str);
extern t_sz		ft_omstream_putc(t_omstream *self, char c);
extern void		ft_omstream_flush(t_omstream *self, int fd);
extern void		ft_omstream_clear(t_omstream *self);
extern t_st		ft_omstream_rewind(t_omstream *self, size_t n);
extern t_st		ft_omstream_forward(t_omstream *self, size_t n);
extern t_st		ft_omstream_seek(t_omstream *self, size_t off);
extern size_t	ft_omstream_tell(t_omstream const *self);

#endif
