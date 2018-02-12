/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/09 19:31:15 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "ps.h"

#define BUFS 4096

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

static inline void	readproc(t_proc *p, t_sds *out)
{
	int		fds[2];
	int		io[3];
	int		status;
	ssize_t	ret;
	char	buf[BUFS + 1];

	ft_memcpy(io, STD_FILENOS, 3 * sizeof(int));
	if (pipe(fds) < 0)
		g_fatalcb(THROW(WUT), NULL);
	io[STDOUT_FILENO] = fds[1];
	p->close = fds[0];
	p->child = 1;
	if (ps_procfork(p, NULL, io, 1))
		return ;
	waitpid(-p->pid, &status, WUNTRACED);
	close(fds[1]);
	while ((ret = read(fds[0], buf, BUFS)) > 0)
	{
		buf[ret] = 0;
		ft_sdsmpush(out, buf, (size_t)ret);
	}
	close(fds[0]);
	while (out->len && out->buf[out->len - 1] == '\n')
		out->buf[--out->len] = '\0';
}

inline void			ps_read(t_sds *dst, t_proccb *cb, t_dtor dtor, void *data)
{
	t_proc proc;

	ps_procfn(&proc, cb, dtor, data);
	readproc(&proc, dst);
	ps_procdtor(&proc);
}
