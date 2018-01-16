/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

inline int	rl_editleft(char const *prompt)
{
	(void)prompt;
	if (g_editln->idx)
	{
		--g_editln->idx;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int	rl_editright(char const *prompt)
{
	(void)prompt;
	if (g_editln->idx != g_editln->str.len)
	{
		++g_editln->idx;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int	rl_edithome(char const *prompt)
{
	if (g_editln->idx)
	{
		g_editln->idx = 0;
		rl_editprint(prompt);
	}
	return (YEP);
}

inline int	rl_editend(char const *prompt)
{
	if (g_editln->idx != g_editln->str.len)
	{
		g_editln->idx = (uint16_t)g_editln->str.len;
		rl_editprint(prompt);
	}
	return (YEP);
}
