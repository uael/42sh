/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EDIT_H
# define MSH_EDIT_H

# include <termios.h>

# include "screen.h"

# ifndef TTY
#  define TTY struct termios
# endif

# define LN_MAX (2048)
# define TC_GOTOUP(N) "\x1b[%dA", (N)
# define TC_GOTODO(N) "\x1b[%dB", (N)
# define TC_GOTOCO(N) "\r\x1b[%dC", (N)
# define TC_UP "\x1b[1A"
# define TC_DO "\x1b[1B"
# define TC_CL "\r\x1b[0K"

# define CAPS_U7 0
# define CAPS_DO 1
# define CAPS_CH 2
# define CAPS_CM 3
# define CAPS_UP 4
# define CAPS_LE 5
# define CAPS_ND 6
# define CAPS_CD 7
# define CAPS_CE 8

typedef struct	s_editln
{
	char		buf[LN_MAX];
	uint16_t	idx;
	uint16_t	len;
	uint16_t	row;
	uint16_t	rows;
}				t_editln;

static t_editln *g_ln;

typedef void	(t_editcb)(t_editln *ln, char const *prompt);

typedef struct	s_editbind
{
	int			rd;
	char const	*key;
	t_editcb	*cb;
}				t_editbind;

extern int		sh_editln(t_editln *ln, char const *prompt, size_t plen);
extern void		sh_editprint(t_editln *ln, char const *prompt);
extern void		sh_editleft(t_editln *ln, char const *prompt);
extern void		sh_editup(t_editln *ln, char const *prompt);
extern void		sh_editdown(t_editln *ln, char const *prompt);
extern void		sh_editright(t_editln *ln, char const *prompt);
extern void		sh_edithome(t_editln *ln, char const *prompt);
extern void		sh_editend(t_editln *ln, char const *prompt);
extern t_bool	sh_getcaps(uint8_t id, char **ret);

#endif
