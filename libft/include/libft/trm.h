/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/trm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/07 11:32:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TRM_H
# define LIBFT_TRM_H

# ifdef __CYGWIN__
#  include <termcap.h>
#  include <termios.h>
# else
#  include <term.h>
# endif

# include "io.h"
# include "lib.h"

# define TRK_TAB 9
# define TRK_ENTER 10
# define TRK_ESC 27
# define TRK_ESCAPE 32
# define TRK_BACKSPACE 127
# define TRK_DELETE 126
# define TRK_UP 65
# define TRK_DOWN 66
# define TRK_RIGHT 67
# define TRK_LEFT 68

extern char		*ft_caps_underline(void);
extern char		*ft_caps_rvideo(void);
extern char		*ft_caps_reset(void);

# ifndef TTY
#  define TTY struct termios
# endif

typedef TTY		t_trmios;

typedef struct	s_trm
{
	t_trmios	tty;
	t_trmios	tmp;
	int			h;
	int			w;
	t_ostream	out;
	t_du8		in;
	t_bool		on;
}				t_trm;

extern t_st		ft_trm_ctor(t_trm *self);
extern void		ft_trm_dtor(t_trm *self);
extern void		ft_trm_refresh(t_trm *self);
extern void		ft_trm_clear(t_trm *self);
extern int		ft_trm_getch(t_trm *self);
extern t_sz		ft_trm_puts(t_trm *self, char const *s);
extern ssize_t	ft_trm_putr(t_trm *self, char c, size_t n);
extern void		ft_trm_on(t_trm *self);
extern void		ft_trm_off(t_trm *self);

#endif
