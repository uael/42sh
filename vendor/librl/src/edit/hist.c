/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline int	rl_editup(void)
{
	if (g_edit_idx)
	{
		if (g_edit_cat && g_edit_idx == g_edit_len - 1)
			--g_edit_idx;
		g_eln = g_edit + --g_edit_idx;
		g_eln->idx = (uint16_t)g_eln->len;
		g_eln->row = (g_eln + 1)->row;
		g_eln->rows.len = (g_eln + 1)->rows.len;
		rl_editprint();
	}
	return (YEP);
}

inline int	rl_editdown(void)
{
	if (g_edit_idx + 1 < g_edit_len)
	{
		if (g_edit_cat && g_edit_idx + 2 == g_edit_len - 1)
			++g_edit_idx;
		g_eln = g_edit + ++g_edit_idx;
		g_eln->idx = (uint16_t)g_eln->len;
		g_eln->row = (g_eln - 1)->row;
		g_eln->rows.len = (g_eln - 1)->rows.len;
		rl_editprint();
	}
	return (YEP);
}
