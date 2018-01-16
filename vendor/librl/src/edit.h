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
# define TC_GOTOFO(N) "\x1b[%dC", (N)
# define TC_GOTOBA(N) "\x1b[%dD", (N)
# define TC_GOTOSU(N) "\x1b[%dS", (N)
# define TC_GOTOSD(N) "\x1b[%dT", (N)
# define TC_GOTOCH(N) "\r\x1b[%dC", (N)
# define TC_CH "\r"
# define TC_UP "\x1b[1A"
# define TC_DO "\x1b[1B"
# define TC_FO "\x1b[1C"
# define TC_BA "\x1b[1D"
# define TC_SU "\x1b[1S"
# define TC_SD "\x1b[1T"
# define TC_CL "\r\x1b[0K"
# define TC_MR "\x1b[7m"
# define TC_ME "\x1b[m"
# define TC_CL_UP TC_CL TC_UP

typedef struct	s_editln
{
	t_sds		str;
	size_t		idx;
	size_t		vidx;
	uint16_t	row;
	t_vec		rows;
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
extern t_editln	*g_eln;
extern t_bool	g_edit_cat;

extern void		rl_editdtor(void);
extern void		rl_editlnupdate(t_editln *ln);
extern int		rl_editln(char const *prompt, size_t *sz, char **l, t_bool cat);
extern void		rl_editprint(char const *prompt);
extern int		rl_editinsert(char const *prompt, char c);
extern int		rl_editdelete(char const *prompt);
extern int		rl_editbackspace(char const *prompt);
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
