/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/istream.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:01:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_ISTREAM_H
# define LIBFT_IO_ISTREAM_H

# include "ifstream.h"
# include "imstream.h"

enum			e_istream
{
	ISTREAM_FILE = 0,
	ISTREAM_MEM
};

union			u_istream
{
	t_ifstream	file;
	t_imstream	mem;
};

typedef struct	s_istream
{
	enum e_istream	kind;
	union u_istream	u;
}				t_istream;

extern t_bool	ft_istream_open(t_istream *self, char const *filename);
extern t_bool	ft_istream_mopen(t_istream *self, char const *str);
extern t_bool	ft_istream_mnopen(t_istream *self, char const *str, size_t n);
extern t_bool	ft_istream_close(t_istream *self);
extern ssize_t	ft_istream_read(t_istream *self, char *buf, size_t len);
extern ssize_t	ft_istream_readf(t_istream *self, char *fmt, ...);
extern ssize_t	ft_istream_vreadf(t_istream *self, char *fmt, va_list ap);
extern char		ft_istream_getc(t_istream *self);
extern ssize_t	ft_istream_get(t_istream *self, char *buf, size_t len);
extern char		ft_istream_peek(t_istream *self, size_t n);
extern void		ft_istream_flush(t_istream *self);
extern t_bool	ft_istream_rewind(t_istream *self, size_t n);
extern t_bool	ft_istream_forward(t_istream *self, size_t n);
extern t_bool	ft_istream_seek(t_istream *self, size_t off);
extern size_t	ft_istream_tell(t_istream const *self);

#endif
