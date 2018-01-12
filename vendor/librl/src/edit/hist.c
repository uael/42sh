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

inline int	rl_editup(char const *prompt)
{
	if (g_edit_idx)
	{
		g_editln = g_edit + --g_edit_idx;
		g_editln->idx = g_editln->str.len;
		g_editln->row = (g_editln + 1)->row;
		g_editln->rows = (g_editln + 1)->rows;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int	rl_editdown(char const *prompt)
{
	if (g_edit_idx + 1 < g_edit_len)
	{
		g_editln = g_edit + ++g_edit_idx;
		g_editln->idx = g_editln->str.len;
		g_editln->row = (g_editln - 1)->row;
		g_editln->rows = (g_editln - 1)->rows;
		rl_editprint(prompt);
	}
	return (YEP);
}
