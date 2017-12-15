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
	if (errno == ENOMEM || errno > ELAST ||
		(!arg && (errno == EBADF || errno == EINVAL)))
	{
		sh_dtor(g_sh);
		exit(ENOMEM);
	}
	return (rcode);
}

inline void			sh_sigint_hdl(int sign)
{
	(void)sign;
	tc_clrln(g_tc);
	sh_prompt(g_sh, SH_PROMPT(g_sh));
}

static inline int	main_av(t_sh *sh, int ac, char **av, char **env)
{
	int i;

	i = 0;
	FT_INIT(sh, t_sh);
	sh->mode = SH_AV;
	while (++i < ac)
	{
		ft_ex_register(0, ft_ex_hdl(sh_on_errno, av[i]), NULL);
		if (sh_init_file(sh, SH_AV, env, av[i]))
			continue ;
		sh_eval(sh);
		sh_dtor(sh);
	}
	return (sh->st);
}

static inline int	main_tty(t_sh *sh, char **env)
{
	t_tc	tc;

	FT_INIT(sh, t_sh);
	ft_ex_register(0, ft_ex_hdl(sh_on_errno, NULL), NULL);
	g_tc = &tc;
	if (isatty(STDIN_FILENO) && !tc_ctor(&tc, env, sh))
		sh_init_file(sh, SH_TTY, env, tc.ttyn);
	else
		sh_init_stream(sh, SH_NOTTY, env, g_cin);
	if (sh->mode == SH_NOTTY)
		sh_eval(sh);
	else
	{
		sh_history_init(sh, ".21shry");
		signal(SIGINT, sh_sigint_hdl);
		while (1)
		{
			sh_prompt(sh, SH_PROMPT(sh));
			if (tc_loop(&tc, sh_keys) < 0)
				break ;
		}
		tc_dtor(&tc);
		sh_history_save(sh, ".21shry");
		signal(SIGINT, SIG_DFL);
	}
	return (ft_dtor(sh->st, (t_dtor)sh_dtor, sh, NULL));
}

int					main(int ac, char **av, char **env)
{
	t_sh	sh;

	g_sh = &sh;
	if (ac > 1)
		return (main_av(&sh, ac, av, env));
	return (main_tty(&sh, env));
}
