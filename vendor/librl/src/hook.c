/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "read.h"

inline void		rl_hook(t_rlhook *hook)
{
	g_rlhook = hook;
}

inline void		rl_complete(t_rlcomp *comp)
{
	g_rlcomp = comp;
}

inline int		rl_reprint(void)
{
	if (g_mode == RL_INSERT)
	{
		rl_editprint();
		return (YEP);
	}
	return (NOP);
}
