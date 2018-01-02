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

#include "msh/edit.h"

#define TC_GOTOUP(N) "\x1b[%dA", (N)
#define TC_GOTODO(N) "\x1b[%dB", (N)
#define TC_GOTOCO(N) "\r\x1b[%dC", (N)
#define TC_UP "\x1b[1A"
#define TC_CL "\r\x1b[0K"

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
			if (c < i)
				++g_idx_up;
			ft_ofswrc(out, '\n');
			++*row;
			g_screen->cursor = 0;
			if (*str == '\n')
			{
				++str;
				continue ;
			}
		}
		++g_screen->cursor;
		ft_ofswrc(out, (unsigned char) *str++);
		if (++c == i)
			g_idx_col = g_screen->cursor;
	}
}

void			sh_editprint(t_editln *ln, char const *prompt)
{
	t_ofs		*out;
	uint16_t	i;

	ft_ofsctor(out = &g_edit_out, STDOUT_FILENO);
	if (ln->row < ln->rows)
		ft_ofswrf(out, TC_GOTODO(ln->rows - ln->row));
	i = 0;
	while (++i <= ln->rows)
		ft_ofswrs(out, TC_CL TC_UP);
	ln->rows = 1;
	g_screen->cursor = 0;
	rl_print(out, prompt, 0, &ln->rows);
	ln->buf[ln->len] = '\0';
	rl_print(out, ln->buf, ln->idx, &ln->rows);
	if (g_idx_up)
		ft_ofswrf(out, TC_GOTOUP(g_idx_up));
	ln->row = ln->rows - g_idx_up;
	if (g_screen->cursor != g_idx_col)
		ft_ofswrf(out, TC_GOTOCO(g_idx_col));
	ft_ofsflush(out);
}
