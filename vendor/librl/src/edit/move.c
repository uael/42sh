/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

/*
** TODO: handle margin when LE available
*/

inline int	rl_editleft(char const *prompt)
{
	if (g_editln->idx)
	{
		--g_editln->idx;
		rl_editprint(prompt);
	}
	return (YEP);
}

/*
** TODO: handle margin when ND available
*/

inline int	rl_editright(char const *prompt)
{
	if (g_editln->idx != g_editln->str.len)
	{
		++g_editln->idx;
		rl_editprint(prompt);
	}
	return (YEP);
}

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

inline int	rl_edithome(char const *prompt)
{
	if (g_editln->idx)
	{
		g_editln->idx = 0;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int	rl_editend(char const *prompt)
{
	if (g_editln->idx != g_editln->str.len)
	{
		g_editln->idx = g_editln->str.len;
		rl_editprint(prompt);
	}
	return (YEP);
}