/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/ostream.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 06:59:04 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_OSTREAM_H
# define LIBFT_IO_OSTREAM_H

# include "ofstream.h"
# include "omstream.h"

enum			e_ostream
{
	OSTREAM_FILE = 0,
	OSTREAM_MEM
};

union			u_ostream
{
	t_ofstream	file;
	t_omstream	mem;
};

typedef struct	s_ostream
{
	enum e_ostream	kind;
	union u_ostream	u;
}				t_ostream;

t_ostream		*g_cout;

extern t_sz		ft_cout_write(char const *sr, size_t l);
extern t_sz		ft_cout_writef(char const *fmt, ...);
extern t_sz		ft_cout_vwritef(char const *f, va_list a);
extern t_sz		ft_cout_puts(char const *str);
extern t_sz		ft_cout_putc(char c);
extern void		ft_cout_flush(void);
extern t_st		ft_cout_rewind(size_t n);
extern t_st		ft_cout_forward(size_t n);
extern t_st		ft_cout_seek(size_t off);
extern size_t	ft_cout_tell(void);

extern t_st		ft_ostream_open(t_ostream *self, char const *filename);
extern void		ft_ostream_mopen(t_ostream *self);
extern t_st		ft_ostream_close(t_ostream *self);
extern t_sz		ft_ostream_write(t_ostream *s, char const *sr, size_t l);
extern t_sz		ft_ostream_writef(t_ostream *self, char const *fmt, ...);
extern t_sz		ft_ostream_vwritef(t_ostream *self, char const *f, va_list a);
extern t_sz		ft_ostream_puts(t_ostream *self, char const *str);
extern t_sz		ft_ostream_putc(t_ostream *self, char c);
extern void		ft_ostream_flush(t_ostream *self);
extern t_st		ft_ostream_rewind(t_ostream *self, size_t n);
extern t_st		ft_ostream_forward(t_ostream *self, size_t n);
extern t_st		ft_ostream_seek(t_ostream *self, size_t off);
extern size_t	ft_ostream_tell(t_ostream const *self);

#endif
