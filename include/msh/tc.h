/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/tc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TC_H
# define MSH_TC_H

# include <libft.h>

typedef TTY		t_tcios;

struct s_tc;

typedef int		(*t_tc_hook)(struct s_tc *self, int ch);

typedef struct	s_tc
{
	t_tcios		curr;
	t_tcios		prev;
	void		*arg;
	int			tty;
	int			col;
	int			row;
	int			sx;
	int			sy;
	int			x;
	int 		y;
	t_dstr		in;
	t_du8		r;
	t_tc_hook	hook[UINT8_MAX];
}				t_tc;

extern char		*g_tcaps[];

extern int		tc_ctor(t_tc *self, char **env, void *arg);
extern void		tc_dtor(t_tc *self);
extern void		tc_pause(t_tc *self);
extern void		tc_resume(t_tc *self);
extern int		tc_putc(t_tc *self, char c);
extern int		tc_puts(t_tc *self, char const *s);
extern int		tc_insc(t_tc *self, char c);
extern int		tc_inss(t_tc *self, char const *s);
extern int		tc_clrln(t_tc *self);
extern int		tc_clr(t_tc *self);
extern int		tc_left(t_tc *self);
extern int		tc_right(t_tc *self);
extern int		tc_up(t_tc *self);
extern int		tc_down(t_tc *self);
extern void		tc_hook(t_tc *self, int ch, t_tc_hook hook);
extern int		tc_loop(t_tc *self);

#endif
