/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 14:53:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>

#include "msh.h"

inline void		sh_exe_av(t_sh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	if (av)
	{
		ft_vstr_ctor(av);
		ft_vstr_pushc(av, exe);
	}
	while ((end = sh_peek(self)) && end->id)
	{
		if (end->id == SH_TOK_WORD && av)
			ft_vstr_pushc(av, ft_tok_ident(end)->buf);
		else if (end->id != SH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		sh_next(self, NULL);
	}
	if (av)
	{
		ft_vstr_grow(av, 1);
		FT_INIT(ft_vstr_end(av), char *);
	}
}
