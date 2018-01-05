/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:02:50 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/hist.h"

static t_histln	g_hist[HIST_MAX] = { 0 };
static uint8_t	g_hist_len = 0;
static uint8_t	g_hist_idx = 0;

t_histln		*sh_histln(void)
{
	return (g_hist + g_hist_idx);
}

t_histln		*sh_histpush(char const *buf)
{
	t_histln *ln;
	t_histln tmp;

	g_hist_idx = (uint8_t)(g_hist_len ? g_hist_len - 1 : 0);
	ln = g_hist + g_hist_idx;
	if (!ln->buf)
		ln->buf = ln->edit.buf;
	else if (!ft_strcmp(ln->buf, buf))
		return (ln);
	if (g_hist_len != HIST_MAX)
		ln = g_hist +
			(g_hist_idx = ++g_hist_len);
	else
	{
		tmp = g_hist[0];
		ft_memmove(g_hist, g_hist + 1, (HIST_MAX - 1) * sizeof(t_histln));
		g_hist[HIST_MAX - 1] = tmp;
		ln->edit.idx = 0;
		ln->edit.row = 0;
		ln->edit.rows = 0;
		ln->len = 0;
		*ln->buf = '\0';
	}
	ft_memcpy(ln->edit.buf, buf, ln->edit.len = (uint16_t)ft_strlen(buf));
	return (ln);
}
