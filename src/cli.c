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

int				main(int ac, char **av, char **env)
{
	t_msh	sh;
	int		i;

	g_sh = &sh;
	if (ac > (i = 0) + 1)
	{
		while (++i < ac)
			if (msh_init_file(&sh, env, av[i]) == 0 && msh(&sh) != RET_ERR)
				msh_dtor(&sh);
		msh_dtor(&sh);
	}
	else if (msh_init_stream(&sh, env, g_cin))
		return (EXIT_FAILURE);
	else
	{
		signal(SIGINT, msh_sigint_hdl);
		while (msh_prompt(&sh, " \033[32m$\033[0m ") == RET_OK)
			if (msh(&sh))
				MSH_EXIT(EXIT_FAILURE, &sh);
		msh_dtor(&sh);
	}
	return (EXIT_SUCCESS);
}
