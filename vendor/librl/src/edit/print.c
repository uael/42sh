/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

static uint16_t	g_idx_col;
static uint16_t	g_idx_up;
static t_ofs	g_edit_out;

static void		rl_print(t_ofs *out, char const *str, uint16_t i, uint16_t *row)
{
	uint16_t	c;

	c = 0;
	g_idx_up = 0;
	g_idx_col = g_screen->cursor;
	while (*str)
	{
		if (g_screen->cursor + 1 == g_screen->width || *str == '\n')
		{
			if (c >= i)
				++g_idx_up;
			ft_ofswrc(out, '\n');
			++*row;
			*(uint16_t *)ft_vecpush(&g_editln->cols) = g_screen->cursor;
			if (*str == '\n')
			{
				if (c++ == i)
					g_idx_col = g_screen->cursor;
				g_screen->cursor = 0;
				++str;
				continue ;
			}
			g_screen->cursor = 0;
		}
		if (c++ == i)
			g_idx_col = g_screen->cursor;
		if (*str == '\t')
			g_screen->cursor += (8 - (g_screen->cursor % 8));
		else
			++g_screen->cursor;
		ft_ofswrc(out, (unsigned char)*str++);
	}
	if (c == i)
		g_idx_col = g_screen->cursor;
}

void			rl_editprint(char const *prompt)
{
	t_ofs		*out;
	uint16_t	i;

	ft_ofsctor(out = &g_edit_out, STDOUT_FILENO);
	if (g_editln->row < g_editln->rows)
		ft_ofswrf(out, TC_GOTODO(g_editln->rows - g_editln->row));
	i = 0;
	while (++i < g_editln->rows)
		ft_ofswrs(out, TC_CL TC_UP);
	ft_ofswrs(out, TC_CL);
	g_editln->rows = 1;
	g_screen->cursor = 0;
	g_editln->cols.len = 0;
	rl_print(out, prompt, 0, &g_editln->rows);
	rl_print(out, g_editln->str.buf, (uint16_t)g_editln->idx, &g_editln->rows);
	*(uint16_t *)ft_vecpush(&g_editln->cols) = g_screen->cursor;
	if (g_idx_up)
		ft_ofswrf(out, TC_GOTOUP(g_idx_up));
	g_editln->row = g_editln->rows - g_idx_up;
	if (g_screen->cursor != g_idx_col)
	{
		if (!g_idx_col)
			ft_ofswrc(out, TC_GOTOCH0());
		else
			ft_ofswrf(out, TC_GOTOCH(g_idx_col));
		g_screen->cursor = g_idx_col;
	}
	ft_ofsflush(out);
}
