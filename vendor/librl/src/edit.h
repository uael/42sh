/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_EDIT_H
# define LIBRL_EDIT_H

# include "hist.h"
# include "screen.h"

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
	t_vec		cols;
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

extern void		rl_editdtor(void);
extern char		*rl_editln(char const *prompt, size_t *len);
extern void		rl_editprint(char const *prompt);
extern int		rl_editins(char const *prompt, char c);
extern int		rl_editreturn(char const *prompt);
extern int		rl_editleft(char const *prompt);
extern int		rl_editright(char const *prompt);
extern int		rl_editup(char const *prompt);
extern int		rl_editdown(char const *prompt);
extern int		rl_editctrlleft(char const *prompt);
extern int		rl_editctrlright(char const *prompt);
extern int		rl_editctrlup(char const *prompt);
extern int		rl_editctrldown(char const *prompt);
extern int		rl_edithome(char const *prompt);
extern int		rl_editend(char const *prompt);

#endif
