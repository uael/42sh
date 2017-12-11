/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:12:44 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define SH_PROMPT(SH) ((SH)->st==0?" \033[32m❯\033[0m ":" \033[31m❯\033[0m ")

static t_sh	*g_sh;

static int 			sh_on_errno(int rcode, void *arg)
{
	if (!errno)
		return (rcode);
	if (arg)
		ft_putf(2, N_SH"%e '%s'\n", errno, arg);
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
	ft_putc(0, '\n');
	sh_prompt(g_sh, SH_PROMPT(g_sh));
}

static inline t_st	main_av(t_sh *sh, int ac, char **av, char **env)
{
	int i;

	i = 0;
	FT_INIT(sh, t_sh);
	while (++i < ac)
	{
		ft_ex_register(0, ft_ex_hdl(sh_on_errno, av[i]), NULL);
		if (ST_OK(sh_init_file(sh, env, av[i])))
		{
			sh_eval(sh);
			sh_dtor(sh);
		}
	}
	return (sh->st);
}

static inline t_st	main_stdin(t_sh *sh, char **env)
{
	t_st	st;

	FT_INIT(sh, t_sh);
	ft_ex_register(0, ft_ex_hdl(sh_on_errno, NULL), NULL);
	if (ISE(st = sh_init_stream(sh, env, g_cin)))
		SH_EXIT(ST_TOENO(st), sh, N_SH"%e\n", ST_TOENO(st));
	if (ST_NOK(st))
		return (ft_dtor(sh->st, (t_dtor)sh_dtor, sh, NULL));
	signal(SIGINT, sh_sigint_hdl);
	while (ST_OK(sh_prompt(sh, SH_PROMPT(sh))))
		if (ISE(st = sh_eval(sh)))
			SH_EXIT(ST_TOENO(st), sh, N_SH"%e\n", ST_TOENO(st));
		else if (ST_NOK(st))
			break ;
	return (ft_dtor(sh->st, (t_dtor)sh_dtor, sh, NULL));
}

int					main(int ac, char **av, char **env)
{
	t_sh	sh;

	g_sh = &sh;
	if (ac > 1)
		return (main_av(&sh, ac, av, env));
	return (main_stdin(&sh, env));
}
