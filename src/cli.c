/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 07:40:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define SH_PROMPT(SH) ((SH)->st==0?" \033[32m❯\033[0m ":" \033[31m❯\033[0m ")

static t_sh			*g_sh;
static t_tc			*g_tc;

static int			sh_on_errno(int rcode, void *arg)
{
	if (!errno)
		return (rcode);
	if (arg)
		ft_putf(2, N_SH"%s: %e\n", arg, errno);
	else
		ft_putf(2, N_SH"%e\n", errno);
	if (errno == ENOMEM || errno == EIO || errno == EINVAL || errno > ELAST)
	{
		sh_dtor(g_sh);
		exit(errno);
	}
	errno = 0;
	return (rcode);
}

inline void			sh_sigint_hdl(int sign)
{
	(void)sign;
	tc_clrln(g_tc);
	sh_prompt(g_sh, SH_PROMPT(g_sh));
}

static inline int	main_tty(t_sh *sh, char **env)
{
	t_tc	tc;
	char	*ln;

	g_tc = &tc;
	ft_ex_register(0, ft_ex_hdl(sh_on_errno, NULL), NULL);
	if (sh_init(sh, env))
		return (WUT);
	if (sh->mode == SH_TTY)
		rl_hist_load(&sh->rl, ".21shry");
	while ((ln = rl_readline(&sh->rl, SH_PROMPT(g_sh))))
	{
		if (sh_eval(sh, ln) < 0)
			break ;
		if (sh->mode == SH_TTY)
			rl_hist_save(&sh->rl, ".21shry");
	}
	if (sh->mode == SH_TTY)
		rl_hist_save(&sh->rl, ".21shry");
	sh_dtor(sh);
	return (sh->st);
}

int					main(int ac, char **av, char **env)
{
	t_sh	sh;

	g_sh = &sh;
	return (main_tty(&sh, env));
}
