/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 11:58:54 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_msh	*g_sh;

inline void		msh_sigint_hdl(int sign)
{
	(void)sign;
	ft_putc(0, '\n');
	msh_prompt(g_sh, " \033[32m$\033[0m ");
}

inline t_st 	main_av(t_msh *sh, int ac, char **av, char **env)
{
	t_st 	st;
	int		i;

	i = 0;
	while (++i < ac)
		if (ST_OK(st = msh_init_file(sh, env, av[i])))
		{
			if (ISE(st = msh(sh)))
				return (ft_exit(ST_TOENO(st), (t_dtor)msh_dtor, sh, "%s: %e",
					"msh", ST_TOENO(st)));
			msh_dtor(sh);
		}
		else if (ISE(st))
			ft_putf(2, "%s: %e", "msh", ST_TOENO(st));
	return (ft_dtor(sh->st, (t_dtor)msh_dtor, &sh, NULL));
}

inline t_st 	main_stdin(t_msh *sh, int ac, char **av, char **env)
{
	t_st 	st;

	if (ISE(st = msh_init_stream(sh, env, g_cin)))
		return (ft_dtor(ST_TOENO(st), (t_dtor)msh_dtor, &sh, "%s: %e",
			"msh", ST_TOENO(st)));
	signal(SIGINT, msh_sigint_hdl);
	while (ST_OK(msh_prompt(sh, " \033[32m$\033[0m ")))
		if (ISE(msh(sh)))
			return (ft_dtor(ST_TOENO(st), (t_dtor) msh_dtor, &sh, "%s: %e",
				"msh", ST_TOENO(st)));
	return (ft_dtor(sh->st, (t_dtor)msh_dtor, &sh, NULL));
}

int				main(int ac, char **av, char **env)
{
	t_msh	sh;

	g_sh = &sh;
	if (ac > 1)
		return (main_av(&sh, ac, av, env));
	return (main_stdin(&sh, ac, av, env));
}
