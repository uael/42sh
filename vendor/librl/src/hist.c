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

static char		g_hist[HIST_MAX][MAX_INPUT + 1] = { { 0, 0, 0 } };
static uint8_t	g_hist_len = 0;

inline char		*rl_histadd(char const *ln, size_t len)
{
	char *histln;

	if (g_hist_len && !ft_strcmp(g_hist[g_hist_len - 1], ln))
		return (g_hist[g_hist_len - 1]);
	if (g_hist_len == HIST_MAX)
	{
		ft_memmove(g_hist, g_hist + HIST_DELTA,
			(size_t)((g_hist_len -= HIST_DELTA) * MAX_INPUT));
		ft_memset(g_hist + g_hist_len, 0, HIST_DELTA * MAX_INPUT);
	}
	histln = g_hist[g_hist_len++];
	return (ft_strncpy(histln, ln, len));
}

inline char		*rl_histcat(char const *ln, size_t len, char c, char **out)
{
	char	*histln;
	size_t	middle;

	if (!g_hist_len)
		ENO_THROW(WUT, EINVAL);
	histln = g_hist[g_hist_len++];
	if (c < 0)
	{
		middle = ft_strlen(histln) + c;
		histln[middle] = '\0';
	}
	else if (c)
	{
		middle = ft_strlen(histln) + 1;
		histln[middle - 1] = c;
		histln[middle] = '\0';
	}
	else
		middle = ft_strlen(histln);
	if (len)
		ft_strncpy(histln + middle, ln, len);
	if (out)
		*out = histln;
	return (histln + middle);
}

inline t_bool	rl_histcpy(uint8_t id, char *dst, size_t *sz)
{
	char	*histln;
	size_t	len;

	if (id >= g_hist_len)
		return (0);
	histln = g_hist[id];
	sz ? (*sz = 0) : 0;
	if ((len = ft_strlen(histln)))
	{
		ft_strncpy(dst, histln, len - 1);
		sz ? (*sz = len - 1) : 0;
	}
	return (1);
}
