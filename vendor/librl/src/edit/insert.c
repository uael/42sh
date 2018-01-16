/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline int	rl_editinsert(char c)
{
	if (c == '\n' || c == '\r')
		return (rl_editreturn());
	ft_sdscput(&g_eln->str, g_eln->idx++, c);
	rl_editprint();
	return (YEP);
}

inline int	rl_editdelete(void)
{
	if (g_eln->idx < g_eln->str.len)
	{
		ft_sdsrem(&g_eln->str, g_eln->idx, NULL);
		rl_editprint();
	}
	return (YEP);
}

inline int	rl_editbackspace(void)
{
	if (g_eln->idx && g_eln->str.len)
	{
		ft_sdsrem(&g_eln->str, --g_eln->idx, NULL);
		rl_editprint();
	}
	return (YEP);
}
