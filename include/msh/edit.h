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

# include <term.h>
# include <termios.h>

# include "hist.h"
# include "screen.h"

# ifndef TTY
#  define TTY struct termios
# endif

# define TC_GOTOUP(N) "\x1b[%dA", (N)
# define TC_GOTODO(N) "\x1b[%dB", (N)
# define TC_GOTOCH(N) "\r\x1b[%dC", (N)
# define TC_GOTOCH0() '\r'
# define TC_UP "\x1b[1A"
# define TC_DO "\x1b[1B"
# define TC_CL "\r\x1b[0K"

# define CAPS_U7 0
# define CAPS_CM 1
# define CAPS_LE 2
# define CAPS_ND 3
# define CAPS_CD 4
# define CAPS_CE 5

typedef struct	s_editln
{
	t_sds		str;
	size_t		idx;
	uint16_t	row;
	uint16_t	rows;
}				t_editln;

typedef int	(t_editcb)(char const *prompt);

typedef struct	s_editbind
{
	int			rd;
	char const	*key;
	t_editcb	*cb;
}				t_editbind;

extern t_editln	g_edit[HIST_MAX + 1];
extern uint8_t	g_edit_len;
extern uint8_t	g_edit_idx;
extern t_editln	*g_editln;

extern char		*sh_editln(char const *prompt, size_t *len);
extern void		sh_editprint(char const *prompt);
extern int		sh_editins(char const *prompt, char c);
extern int		sh_editreturn(char const *prompt);
extern int		sh_editleft(char const *prompt);
extern int		sh_editup(char const *prompt);
extern int		sh_editdown(char const *prompt);
extern int		sh_editright(char const *prompt);
extern int		sh_edithome(char const *prompt);
extern int		sh_editend(char const *prompt);
extern t_bool	sh_getcaps(uint8_t id, char **ret);

#endif
