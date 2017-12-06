/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/ifstream.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 16:35:30 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_IFSTREAM_H
# define LIBFT_IO_IFSTREAM_H

# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# include "../int.h"
# include "../str.h"

# ifndef FT_PAGE_SIZE
#  if defined PAGE_SIZE && PAGE_SIZE <= 4096
#   define FT_PAGE_SIZE PAGE_SIZE
#  elif defined PAGESIZE && PAGESIZE <= 4096
#   define FT_PAGE_SIZE PAGESIZE
#  else
#   define FT_PAGE_SIZE 4096
#  endif
# endif

typedef struct	s_ifstream
{
	char const	*filename;
	int			fd;
	char		*buf;
	size_t		beg;
	size_t		cur;
	size_t		end;
	size_t		cap;
	size_t		len;
}				t_ifstream;

extern t_st		ft_ifstream_cin(t_ifstream *self);
extern t_st		ft_ifstream_open(t_ifstream *self, char const *filename);
extern t_st		ft_ifstream_close(t_ifstream *self);
extern t_sz		ft_ifstream_read(t_ifstream *self, char *buf, size_t len);
extern t_sz		ft_ifstream_readf(t_ifstream *self, char *fmt, ...);
extern t_sz		ft_ifstream_vreadf(t_ifstream *self, char *fmt, va_list ap);
extern t_sz		ft_ifstream_get(t_ifstream *self, char *buf, size_t n);
extern t_st		ft_ifstream_peek(t_ifstream *self, char *c, size_t n);
extern void		ft_ifstream_flush(t_ifstream *self);
extern t_st		ft_ifstream_rewind(t_ifstream *self, size_t n);
extern t_st		ft_ifstream_forward(t_ifstream *self, size_t n);
extern t_st		ft_ifstream_seek(t_ifstream *self, size_t off);
extern size_t	ft_ifstream_tell(t_ifstream const *self);

#endif
