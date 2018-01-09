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

#include "msh/edit.h"

/*
** TODO: handle margin when LE available
*/

inline int	sh_editleft(char const *prompt)
{
	char *caps;

	if (g_editln->idx)
	{
		--g_editln->idx;
		if (g_editln->rows == 1 && sh_getcaps(CAPS_LE, &caps))
			ft_putf(1, caps);
		else
			sh_editprint(prompt);
	}
	return (YEP);
}

/*
** TODO: handle margin when ND available
*/

inline int	sh_editright(char const *prompt)
{
	char *caps;

	if (g_editln->idx != g_editln->str.len)
	{
		++g_editln->idx;
		if (g_editln->rows == 1 && sh_getcaps(CAPS_ND, &caps))
			ft_putf(1, caps);
		else
			sh_editprint(prompt);
	}
	return (YEP);
}

inline int	sh_editup(char const *prompt)
{
	if (g_edit_idx)
	{
		g_editln = g_edit + --g_edit_idx;
		g_editln->idx = g_editln->str.len;
		g_editln->row = (g_editln + 1)->row;
		g_editln->rows = (g_editln + 1)->rows;
		sh_editprint(prompt);
	}
	return (YEP);
}

inline int	sh_editdown(char const *prompt)
{
	if (g_edit_idx + 1 < g_edit_len)
	{
		g_editln = g_edit + ++g_edit_idx;
		g_editln->idx = g_editln->str.len;
		g_editln->row = (g_editln - 1)->row;
		g_editln->rows = (g_editln - 1)->rows;
		sh_editprint(prompt);
	}
	return (YEP);
}

inline int	sh_edithome(char const *prompt)
{
	if (g_editln->idx)
	{
		g_editln->idx = 0;
		sh_editprint(prompt);
	}
	return (YEP);
}

inline int	sh_editend(char const *prompt)
{
	if (g_editln->idx != g_editln->str.len)
	{
		g_editln->idx = g_editln->str.len;
		sh_editprint(prompt);
	}
	return (YEP);
}