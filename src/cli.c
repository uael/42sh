/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 18:39:29 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_sh	*g_sh;

inline char			*prompt_in(t_sh *self)
{
	if (self->st == 0)
		return (" \033[32m❯\033[0m ");
	return (" \033[31m❯\033[0m ");
}

inline void			sh_sigint_hdl(int sign)
{
	(void)sign;
	ft_putc(0, '\n');
	sh_prompt(g_sh, prompt_in(g_sh));
}

static inline t_st	main_av(t_sh *sh, int ac, char **av, char **env)
{
	t_st	st;
	int		i;

	i = 0;
	FT_INIT(sh, t_sh);
	while (++i < ac)
		if (ST_OK(st = sh_init_file(sh, env, av[i])))
		{
			if (ISE(st = msh(sh)))
				SH_EXIT(ST_TOENO(st), sh, "%s: %e\n", "21sh", ST_TOENO(st));
			sh_dtor(sh);
		}
		else if (ISE(st))
			ft_putf(2, "%s: %e '%s'\n", "21sh", ST_TOENO(st), av[i]);
	return (ft_dtor(sh->st, (t_dtor)sh_dtor, sh, NULL));
}

static inline t_st	main_stdin(t_sh *sh, char **env)
{
	t_st	st;

	FT_INIT(sh, t_sh);
	if (ISE(st = sh_init_stream(sh, env, g_cin)))
		SH_EXIT(ST_TOENO(st), sh, "%s: %e\n", "21sh", ST_TOENO(st));
	if (ST_NOK(st))
		return (ft_dtor(sh->st, (t_dtor)sh_dtor, sh, NULL));
	signal(SIGINT, sh_sigint_hdl);
	while (ST_OK(sh_prompt(sh, prompt_in(sh))))
		if (ISE(st = msh(sh)))
			SH_EXIT(ST_TOENO(st), sh, "%s: %e\n", "21sh", ST_TOENO(st));
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
