/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"


inline int	rl_editappend(char const *prompt, char *s, size_t sz)
{
	char *eol;

	if ((eol = ft_strnchr(s, '\n', sz)) ||
		(eol = ft_strnchr(s, '\r', sz)))
	{
		ft_sdsmput(&g_eln->str, g_eln->idx, s, eol - s);
		g_eln->idx += eol - s;
		rl_editprint(prompt);
		if (*eol == '\r' && *(eol + 1) == '\n')
			++eol;
		if ((size_t)(++eol - s) < sz)
			ft_sdsmpush(&g_edit_swap, eol, sz - (eol - s));
		return (rl_editreturn(prompt));
	}
	ft_sdsmput(&g_eln->str, g_eln->idx, s, sz);
	g_eln->idx += sz;
	rl_editprint(prompt);
	return (YEP);
}

inline int	rl_editdelete(char const *prompt)
{
	if (g_eln->idx < g_eln->str.len)
	{
		ft_sdsrem(&g_eln->str, g_eln->idx, NULL);
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int	rl_editbackspace(char const *prompt)
{
if (g_eln->idx && g_eln->str.len)
{
ft_sdsrem(&g_eln->str, --g_eln->idx, NULL);
rl_editprint(prompt);
}
return (YEP);
}
