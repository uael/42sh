/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

t_map			*g_binaries = &g_binaries_stack;
t_map			*g_builtins = &g_builtins_stack;
t_errcb			*g_errcb;
t_fatalcb		*g_fatalcb;
t_bool			g_tty = 0;
pid_t			g_pgid = 0;
pid_t			g_pid = 0;
TTY				g_tcmode;

inline int		ps_init(int fd, t_errcb *errcb, t_fatalcb *fatalcb)
{
	g_errcb = errcb;
	g_fatalcb = fatalcb;
	tcgetattr(fd, &g_tcmode);
	g_tty = (t_bool)isatty(fd);
	g_pgid = getpid();
	return (YEP);
}

inline pid_t	ps_lastpid(void)
{
	return (g_pid);
}

inline void		ps_dtor(void)
{
	ft_mapdtor(g_binaries, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
	ft_mapdtor(g_builtins, (t_dtor)ft_pfree, NULL);
}
