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

static inline void		onprint(t_ofs *out, char const *row, char const *pos)
{
	char		*vis;

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
		if (row == vis)
		{
			if (vis > pos)
				ft_ofswrs(out, TC_ME);
			else if (vis < pos)
				ft_ofswrs(out, TC_MR);
		}
	}
}

static inline void		doprint(t_ofs *out, char const *row, char const *pos,
								 char const *eol)
{
	while (row < eol)
	{
		onprint(out, row, pos);
		g_screen->col += *row == '\t' ? (8 - (g_screen->col % 8)) : 1;
		ft_ofswrc(out, (unsigned char)*row++);
	}
	onprint(out, row, pos);
}

static inline void		println(t_ofs *out, size_t i, uint16_t plen)
{
	char	*pos;
	char	*row;
	char	*eol;

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
		doprint(out, row, pos, eol);
		if (++i < g_eln->rows.len)
			ft_ofswrc(out, '\n');
		plen = 0;
	}
}

static inline uint16_t	printprompt(t_ofs *out, char const *prompt)
{
	uint16_t	i;

	i = 0;
	while (*prompt)
	{
		if (g_screen->col + 1 == g_screen->width)
		{
			++i;
			ft_ofswrc(out, '\n');
			g_screen->col = 0;
			break ;
		}
		g_screen->col += *prompt == '\t' ? (8 - (g_screen->col % 8)) : 1;
		ft_ofswrc(out, (unsigned char)*prompt++);
	}
	return (i);
}

void					rl_editprint(char const *prompt)
{
	t_ofs		*out;
	uint16_t	i;

	ft_ofsctor(out = &g_edit_out, STDOUT_FILENO);
	if (g_eln->row < g_eln->rows.len)
		ft_ofswrf(out, TC_GOTODO(g_eln->rows.len - g_eln->row));
	i = 0;
	while (++i < g_eln->rows.len)
		ft_ofswrs(out, TC_CL TC_UP);
	ft_ofswrs(out, TC_CL);
	g_screen->col = 0;
	g_idx_up = 0;
	rl_editlnupdate(g_eln);
	println(out, printprompt(out, prompt), g_screen->col);
	if (g_idx_up)
		ft_ofswrf(out, TC_GOTOUP(g_idx_up));
	g_eln->row = (uint16_t)(g_eln->rows.len - g_idx_up);
	if (!g_idx_col)
		ft_ofswrs(out, TC_GOTOCH0);
	else
		ft_ofswrf(out, TC_GOTOCH(g_idx_col));
	g_screen->col = g_idx_col;
	ft_ofsflush(out);
}
