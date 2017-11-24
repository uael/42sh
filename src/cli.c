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
	t_msh sh;

	(void)ac;
	(void)av;
	if (msh_init_stream(&sh, env, g_cin))
		return (EXIT_FAILURE);
	g_sh = &sh;
	signal(SIGINT, msh_sigint_hdl);
	while (msh_prompt(&sh, " \033[32m$\033[0m ") == RET_OK)
		if (msh(&sh))
		{
			msh_dtor(&sh);
			return (EXIT_FAILURE);
		}
	msh_dtor(&sh);
	return (EXIT_SUCCESS);
}
