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

static uint16_t			g_idx_col;
static uint16_t			g_idx_up;
static t_ofs			g_edit_out_stack = {STDIN_FILENO, 0, {0}};
static t_ofs			*g_out = &g_edit_out_stack;

static inline void			onprint(t_ofs *out, char const *row,
	char const *pos)
{
	char *vis;

	if (row == pos)
		g_idx_col = g_screen->col;
	if (g_mode == RL_VISUAL)
	{
		vis = ft_sdsat(&g_eln->str, g_eln->vidx);
		if (row == pos)
		{
			if (pos > vis)
				ft_ofswrs(out, TC_ME);
			else if (pos < vis)
				ft_ofswrs(out, TC_MR);
		}
		else if (row == vis)
		{
			if (vis > pos)
				ft_ofswrs(out, TC_ME);
			else if (vis < pos)
				ft_ofswrs(out, TC_MR);
		}
	}
}

static inline void			printrow(char const *r, char const *p,
	char const *eol)
{
	while (r < eol)
	{
		onprint(g_out, r, p);
		g_screen->col += *r == '\t' ? (8 - (g_screen->col % 8)) : 1;
		ft_ofswrc(g_out, (unsigned char)*r++);
	}
	onprint(g_out, r, p);
}

static inline void			println(size_t i, uint16_t plen)
{
	char *pos;
	char *row;
	char *eol;

	pos = ft_sdsat(&g_eln->str, g_eln->idx);
	while (i < g_eln->rows.len)
	{
		g_screen->col = plen;
		row = *((char **)g_eln->rows.buf + i);
		eol = row;
		while (*eol && *eol != '\n')
			++eol;
		g_idx_up = (uint16_t)((pos >= row && pos <= eol) ? 0 : g_idx_up + 1);
		if (pos >= row && pos <= eol && pos - row > g_screen->width - plen - 1)
		{
			row = pos - (g_screen->width - plen - 1);
			eol = pos;
		}
		else if (eol - row > g_screen->width - plen - 1)
			eol = row + (g_screen->width - plen - 1);
		printrow(row, pos, eol);
		if (++i < g_eln->rows.len)
			ft_ofswrc(g_out, '\n');
		plen = 0;
	}
}

static inline uint16_t		printprompt(void)
{
	uint16_t	i;
	char		*p;

	i = 0;
	p = g_edit_prompt;
	while (*p)
	{
		if (g_screen->col + 1 == g_screen->width)
		{
			++i;
			ft_ofswrc(g_out, '\n');
			g_screen->col = 0;
			break ;
		}
		g_screen->col += *p == '\t' ? (8 - (g_screen->col % 8)) : 1;
		ft_ofswrc(g_out, (unsigned char)*p++);
	}
	return (i);
}

inline void					rl_editprint(void)
{
	uint16_t i;

	if (g_eln->row < g_eln->rows.len)
		ft_ofswrf(g_out, TC_GOTODO(g_eln->rows.len - g_eln->row));
	i = 0;
	while (++i < g_eln->rows.len)
		ft_ofswrs(g_out, TC_CL_UP);
	ft_ofswrs(g_out, TC_CL);
	g_screen->col = 0;
	g_idx_up = 0;
	rl_editlnupdate(g_eln);
	i = printprompt();
	println(i, (uint16_t)rl_wstrlen(g_edit_prompt));
	if (g_idx_up)
		ft_ofswrf(g_out, TC_GOTOUP(g_idx_up));
	g_eln->row = (uint16_t)(g_eln->rows.len - g_idx_up);
	if (!g_idx_col)
		ft_ofswrs(g_out, TC_CH);
	else
		ft_ofswrf(g_out, TC_GOTOCH(g_idx_col));
	g_screen->col = g_idx_col;
	ft_ofsflush(g_out);
}
