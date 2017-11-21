/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/imstream.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:01:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_IMSTREAM_H
# define LIBFT_IO_IMSTREAM_H

# include "ifstream.h"

typedef struct	s_imstream
{
	char const	*buf;
	size_t		cur;
	size_t		len;
}				t_imstream;

extern t_bool	ft_imstream_open(t_imstream *self, char const *str);
extern t_bool	ft_imstream_nopen(t_imstream *self, char const *str, size_t n);
extern t_bool	ft_imstream_close(t_imstream *self);
extern ssize_t	ft_imstream_read(t_imstream *self, char *buf, size_t len);
extern ssize_t	ft_imstream_readf(t_imstream *self, char *fmt, ...);
extern ssize_t	ft_imstream_vreadf(t_imstream *self, char *fmt, va_list ap);
extern char		ft_imstream_getc(t_imstream *self);
extern ssize_t	ft_imstream_get(t_imstream *self, char *buf, size_t len);
extern char		ft_imstream_peek(t_imstream *self, size_t n);
extern void		ft_imstream_flush(t_imstream *self);
extern t_bool	ft_imstream_rewind(t_imstream *self, size_t n);
extern t_bool	ft_imstream_forward(t_imstream *self, size_t n);
extern t_bool	ft_imstream_seek(t_imstream *self, size_t off);
extern size_t	ft_imstream_tell(t_imstream const *self);

#endif
