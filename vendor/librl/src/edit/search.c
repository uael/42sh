/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:13:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "search.h"

void			searchprint(void)
{
	char		buf[PATH_MAX];

	buf[0] = '(';
	buf[1] = '\0';
	if (g_lookup->len)
		ft_strcat(buf, g_lookup->buf);
	ft_strcat(buf, ") ");
	ft_strcat(buf, g_edit_prompt);
	rl_editprint(buf, g_candidate);
}

inline int		rl_searchtoggle(void)
{
	uint16_t i;

	if (g_mode == RL_SEARCH)
	{
		g_mode = RL_INSERT;
		rl_editprint(g_edit_prompt, g_eln);
	}
	else if (g_mode != RL_NONE)
	{
		g_mode = RL_SEARCH;
		if (g_eln->row < g_eln->rows.len)
			ft_ofswrf(g_out, TC_GOTODO(g_eln->rows.len - g_eln->row));
		i = 0;
		while (++i < g_eln->rows.len)
			ft_ofswrs(g_out, TC_CL_UP);
		ft_ofswrs(g_out, TC_CL);
		ft_ofsflush(g_out);
		g_eln->row = 0;
		g_eln->rows.len = 0;
		ft_sdsgrow(g_lookup, 1);
		*g_lookup->buf = '\0';
		g_lookup->len = 0;
		g_screen->col = 0;
		g_idx = 0;
		ft_memset(g_candidate, 0, sizeof(t_editln));
		searchprint();
	}
	return (YEP);
}

inline int		rl_searchinsert(char c)
{
	if (c == '\n' || c == '\r')
		return (YEP);
	ft_sdscput(g_lookup, g_idx++, c);
	searchprint();
	return (YEP);
}

inline int		rl_searchbackspace(void)
{
	if (g_idx && g_lookup->len)
	{
		ft_sdsrem(g_lookup, --g_idx, NULL);
		searchprint();
	}
	return (YEP);
}
