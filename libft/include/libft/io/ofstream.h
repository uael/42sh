/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/ofstream.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 09:41:00 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_OFSTREAM_H
# define LIBFT_IO_OFSTREAM_H

# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# include "../int.h"
# include "../str.h"
# include "../ex.h"

# ifndef FT_PAGE_SIZE
#  if defined PAGE_SIZE && PAGE_SIZE <= 4096
#   define FT_PAGE_SIZE PAGE_SIZE
#  elif defined PAGESIZE && PAGESIZE <= 4096
#   define FT_PAGE_SIZE PAGESIZE
#  else
#   define FT_PAGE_SIZE 4096
#  endif
# endif

typedef struct	s_ofstream
{
	char const	*filename;
	int			fd;
	char		*buf;
	size_t		beg;
	size_t		cur;
	size_t		end;
	size_t		len;
}				t_ofstream;

extern int		ft_ofstream_open(t_ofstream *self, char const *filename);
extern int		ft_ofstream_close(t_ofstream *self);
extern ssize_t	ft_ofstream_write(t_ofstream *s, char const *sr, size_t l);
extern ssize_t	ft_ofstream_writef(t_ofstream *self, char const *fmt, ...);
extern ssize_t	ft_ofstream_vwritef(t_ofstream *self, char const *f, va_list a);
extern ssize_t	ft_ofstream_puts(t_ofstream *self, char const *str);
extern int		ft_ofstream_putc(t_ofstream *self, char c);
extern void		ft_ofstream_flush(t_ofstream *self);
extern int		ft_ofstream_rewind(t_ofstream *self, size_t n);
extern int		ft_ofstream_forward(t_ofstream *self, size_t n);
extern int		ft_ofstream_seek(t_ofstream *self, size_t off);
extern size_t	ft_ofstream_tell(t_ofstream const *self);

#endif
