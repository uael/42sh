/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/term.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:01:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TERM_H
# define LIBFT_TERM_H

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

typedef enum	e_term_mode
{
	TERM_OFF,
	TERM_NOTTY,
	TERM_INSERT,
	TERM_VISUAL
}				t_term_mode;

typedef struct	s_term_curs
{
	size_t		i;
	uint32_t	x;
	uint32_t	y;
}				t_term_curs;

typedef struct	s_term
{
	t_term_mode	mode;
	int			fd;
	char		*history_fn;
	t_vstr		history;
	size_t		hcurs;
	t_termios	on;
	t_termios	off;
	t_term_curs	curs;
	t_dstr		line;
	size_t		col;
	size_t		row;
}				t_term;

extern int		ft_term_ctor(t_term *self, char **env, char *history);
extern void		ft_term_dtor(t_term *self);

extern char		*ft_readline(t_term *term, char *prompt);

#endif
