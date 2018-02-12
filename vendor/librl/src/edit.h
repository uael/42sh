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
# include "signal.h"

# define TC_GOTOUP(N) "\x1b[%dA", (N)
# define TC_GOTODO(N) "\x1b[%dB", (N)
# define TC_GOTOCH(N) "\r\x1b[%dC", (N)
# define TC_CH "\r"
# define TC_UP "\x1b[1A"
# define TC_CL "\r\x1b[0K"
# define TC_MR "\x1b[7m"
# define TC_ME "\x1b[m"
# define TC_CL_UP TC_CL TC_UP
# define TC_ED "\x1b[2J"
# define TC_ED_CUP TC_ED "\x1b[0;0H"

# define RL_EXIT 3
# define RL_CLR 4

typedef struct	s_editln
{
	t_sds		str;
	size_t		idx;
	size_t		vidx;
	uint16_t	row;
	t_vec		rows;
}				t_editln;

typedef int	(t_editcb)(void);

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
extern char		*g_edit_prompt;
extern t_rlhook	*g_rlhook;
extern t_rlcomp	*g_rlcomp;

extern void		rl_editdtor(void);
extern int		rl_wstrlen(char *str);
extern void		rl_editlnupdate(t_editln *ln);
extern int		rl_editln(char const *prompt, size_t *sz, char **l, t_bool cat);
extern void		rl_editprint(char *prompt, t_editln *ln);
extern int		rl_editinsert(char c);
extern int		rl_editdelete(void);
extern int		rl_editbackspace(void);
extern int		rl_editclear(void);
extern int		rl_editreturn(void);
extern int		rl_editleft(void);
extern int		rl_editright(void);
extern int		rl_editup(void);
extern int		rl_editdown(void);
extern int		rl_editctrlleft(void);
extern int		rl_editctrlright(void);
extern int		rl_editctrlup(void);
extern int		rl_editctrldown(void);
extern int		rl_edithome(void);
extern int		rl_editend(void);
extern int		rl_edittab(void);
extern void		rl_visualdtor(void);
extern int		rl_visualtoggle(void);
extern int		rl_visualyank(void);
extern int		rl_visualdelete(void);
extern int		rl_visualpaste(void);
extern int		rl_searchtoggle(void);
extern int		rl_searchinsert(char c);
extern int		rl_searchbackspace(void);

#endif
