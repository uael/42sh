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
#include "../read.h"

static uint16_t	g_idx_col;
static uint16_t	g_idx_up;
static t_ofs	g_edit_out;

static void		rl_print(t_ofs *out, char const *str, t_bool o, uint16_t *row)
{
	uint16_t	c;

	c = 0;
	g_idx_up = 0;
	g_idx_col = g_screen->col;
	while (*str)
	{
		if (g_screen->col + 1 == g_screen->width || *str == '\n')
		{
			if (o && c >= g_editln->idx)
				++g_idx_up;
			ft_ofswrc(out, '\n');
			++*row;
			*(uint16_t *)ft_vecpush(&g_editln->cols) = g_screen->col;
			if (*str == '\n')
			{
				if (o && c++ == g_editln->idx)
					g_idx_col = g_screen->col;
				g_screen->col = 0;
				++str;
				continue ;
			}
			g_screen->col = 0;
		}
		if (o && g_mode == RL_VISUAL)
		{
			if (c == g_editln->idx)
			{
				if (c > g_editln->vidx)
					ft_ofswrs(out, TC_ME);
				else if (c < g_editln->vidx)
					ft_ofswrs(out, TC_MR);
			}
			if (c == g_editln->vidx)
			{
				if (c > g_editln->idx)
					ft_ofswrs(out, TC_ME);
				else if (c < g_editln->idx)
					ft_ofswrs(out, TC_MR);
			}
		}
		if (o && c++ == g_editln->idx)
			g_idx_col = g_screen->col;
		if (*str == '\t')
			g_screen->col += (8 - (g_screen->col % 8));
		else
			++g_screen->col;
		ft_ofswrc(out, (unsigned char)*str++);
	}
	if (o && g_mode == RL_VISUAL)
	{
		if (c == g_editln->idx)
		{
			if (c > g_editln->vidx)
				ft_ofswrs(out, TC_ME);
			else if (c < g_editln->vidx)
				ft_ofswrs(out, TC_MR);
		}
		if (c == g_editln->vidx)
		{
			if (c > g_editln->idx)
				ft_ofswrs(out, TC_ME);
			else if (c < g_editln->idx)
				ft_ofswrs(out, TC_MR);
		}
	}
	if (o && c == g_editln->idx)
		g_idx_col = g_screen->col;
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
	g_screen->col = 0;
	g_editln->cols.len = 0;
	rl_print(out, prompt, 0, &g_editln->rows);
	rl_print(out, g_editln->str.buf, 1, &g_editln->rows);
	*(uint16_t *)ft_vecpush(&g_editln->cols) = g_screen->col;
	if (g_idx_up)
		ft_ofswrf(out, TC_GOTOUP(g_idx_up));
	g_editln->row = g_editln->rows - g_idx_up;
	if (g_screen->col != g_idx_col)
	{
		if (!g_idx_col)
			ft_ofswrs(out, TC_GOTOCH0);
		else
			ft_ofswrf(out, TC_GOTOCH(g_idx_col));
		g_screen->col = g_idx_col;
	}
	ft_ofsflush(out);
}
