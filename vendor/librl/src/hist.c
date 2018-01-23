/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hist.h"

static t_sds	g_hist[HIST_MAX] = { { 0, 0, 0 } };
static uint8_t	g_hist_len = 0;

inline char		*rl_histadd(char const *ln, size_t len)
{
	t_sds	*histln;
	size_t	i;

	if (g_hist_len && !ft_strcmp(g_hist[g_hist_len - 1].buf, ln))
		return (g_hist[g_hist_len - 1].buf);
	if (g_hist_len == HIST_MAX)
	{
		i = 0;
		while (i < HIST_DELTA)
			ft_sdsdtor(g_hist + i++);
		ft_memmove(g_hist, g_hist + HIST_DELTA,
			(g_hist_len -= HIST_DELTA) * sizeof(t_sds));
		ft_memset(g_hist + g_hist_len, 0, HIST_DELTA * sizeof(t_sds));
	}
	histln = g_hist + g_hist_len++;
	histln->len = 0;
	if (len)
		ft_sdsmpush(histln, ln, len);
	return (histln->buf);
}

inline char		*rl_histcat(char const *ln, size_t len, char c, char **out)
{
	t_sds		*histln;
	size_t		middle;

	if (!g_hist_len)
		ENO_THROW(WUT, EINVAL);
	histln = g_hist + g_hist_len - 1;
	if (c < 0)
	{
		middle = histln->len + c;
		ft_sdsnpop(histln, (size_t)-c, NULL);
	}
	else if (c)
	{
		middle = histln->len + 1;
		ft_sdscpush(histln, c);
	}
	else
		middle = histln->len;
	if (len)
		ft_sdsmpush(histln, ln, len);
	if (out)
		*out = histln->buf;
	return (histln->buf + middle);
}

inline t_bool	rl_histcpy(uint8_t id, t_sds *dest)
{
	t_sds *histln;

	if (id >= g_hist_len)
		return (0);
	histln = g_hist + id;
	dest->len = 0;
	if (histln->len)
	{
		ft_sdsmpush(dest, histln->buf, histln->len);
		ft_sdspop(dest, NULL);
	}
	return (1);
}

inline void		rl_histdtor(void)
{
	uint8_t i;

	i = 0;
	while (i < g_hist_len)
		ft_sdsdtor(g_hist + i++);
	g_hist_len = 0;
}
