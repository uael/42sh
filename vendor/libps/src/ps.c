/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/13 00:10:27 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "ps.h"

#define BUFS 4096

static t_map		g_binaries_stack = {
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
static t_map		g_builtins_stack = {
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(t_procbi *), NULL, NULL
};

t_map				*g_binaries = &g_binaries_stack;
t_map				*g_builtins = &g_builtins_stack;
t_errcb				*g_errcb;
t_fatalcb			*g_fatalcb;
t_bool				g_tty = 0;
pid_t				g_pgid = 0;
pid_t				g_pid = 0;
TTY					g_tcmode;

inline int			ps_init(int fd, t_errcb *errcb, t_fatalcb *fatalcb)
{
	g_errcb = errcb;
	g_fatalcb = fatalcb;
	tcgetattr(fd, &g_tcmode);
	g_tty = (t_bool)isatty(fd);
	g_pgid = getpid();
	ps_biregister("bg", ps_bibg);
	ps_biregister("fg", ps_bifg);
	ps_biregister("jobs", ps_bijobs);
	rl_hook(ps_poolnotify);
	return (YEP);
}

inline pid_t		ps_lastpid(void)
{
	return (g_pid);
}

inline void			ps_dtor(void)
{
	size_t	i;

	i = 0;
	while (i < ps_poollen())
		ps_jobkill(ps_poolget(i++));
	ft_mapdtor(g_binaries, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
	ft_mapdtor(g_builtins, (t_dtor)ft_pfree, NULL);
}
