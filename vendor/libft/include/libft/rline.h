/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/rline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:01:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_RLINE_H
# define LIBFT_RLINE_H

# include "io.h"
# include "ds.h"

# ifdef __CYGWIN__
#  include <termcap.h>
#  include <termios.h>
# else
#  include <term.h>
# endif

# ifndef TTY
#  define TTY struct termios
# endif

typedef TTY		t_termios;

typedef enum	e_rline_m
{
	TERM_OFF,
	TERM_NOTTY,
	TERM_INSERT,
	TERM_VISUAL
}				t_rline_m;

typedef struct	s_rline
{
	t_rline_m	mode;
	int			ifd;
	int			ofd;
	char		*buf;
	size_t		blen;
	const char	*prompt;
	size_t		plen;
	size_t		pos;
	size_t		oldpos;
	size_t		len;
	size_t		cols;
	size_t		maxrows;
	t_vstr		histo;
	int			hidx;
}				t_rline;

extern char		*ft_readline(t_rline *term, char *prompt);

#endif
