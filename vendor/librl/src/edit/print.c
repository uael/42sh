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

static uint16_t			g_icol;
static uint16_t			g_iup;
static t_ofs			g_edit_out_stack = {STDOUT_FILENO, 0, {0}};
static t_ofs			*g_out = &g_edit_out_stack;

static inline void			onprint(t_editln *ln, t_ofs *out, char const *row,
	char const *pos)
{
	char *vis;

	if (row == pos)
		g_icol = g_screen->col;
	if (g_mode == RL_VISUAL)
	{
		vis = ft_sdsat(&ln->str, ln->vidx);
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

static inline void			printrow(t_editln *ln, char const *r, char const *p,
	char const *eol)
{
	while (r < eol)
	{
		onprint(ln, g_out, r, p);
		g_screen->col += *r == '\t' ? (8 - (g_screen->col % 8)) : 1;
		ft_ofswrc(g_out, (unsigned char)*r++);
	}
	onprint(ln, g_out, r, p);
}

static inline void			println(t_editln *ln, size_t i, uint16_t plen)
{
	char *pos;
	char *row;
	char *eol;

	pos = ft_sdsat(&ln->str, ln->idx);
	while (i < ln->rows.len)
	{
		g_screen->col = plen;
		row = *((char **)ln->rows.buf + i);
		eol = row;
		while (*eol && *eol != '\n')
			++eol;
		g_iup = (uint16_t)((pos >= row && pos <= eol) ? 0 : g_iup + 1);
		if (pos >= row && pos <= eol && pos - row > g_screen->width - plen - 1)
		{
			row = pos - (g_screen->width - plen - 1);
			eol = pos;
		}
		else if (eol - row > g_screen->width - plen - 1)
			eol = row + (g_screen->width - plen - 1);
		printrow(ln, row, pos, eol);
		if (++i < ln->rows.len)
			ft_ofswrc(g_out, '\n');
		plen = 0;
	}
}

static inline uint16_t		printprompt(char *prompt)
{
	uint16_t	i;
	char		*p;

	i = 0;
	p = prompt;
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

inline void					rl_editprint(char *prompt, t_editln *ln)
{
	uint16_t i;

	if (ln->row < ln->rows.len)
		ft_ofswrf(g_out, TC_GOTODO(ln->rows.len - ln->row));
	i = 0;
	while (++i < ln->rows.len)
		ft_ofswrs(g_out, TC_CL_UP);
	ft_ofswrs(g_out, TC_CL);
	g_screen->col = 0;
	g_iup = 0;
	i = printprompt(prompt);
	if (!ln->str.len)
	{
		ft_ofsflush(g_out);
		return ;
	}
	rl_editlnupdate(ln);
	println(ln, i, (uint16_t)rl_wstrlen(prompt));
	if (g_iup)
		ft_ofswrf(g_out, TC_GOTOUP(g_iup));
	ln->row = (uint16_t)(ln->rows.len - g_iup);
	g_icol ? ft_ofswrf(g_out, TC_GOTOCH(g_icol)) : ft_ofswrs(g_out, TC_CH);
	g_screen->col = g_icol;
	ft_ofsflush(g_out);
}
