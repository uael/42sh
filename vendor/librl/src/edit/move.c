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
	uint16_t ch;

	(void)prompt;
	if (g_editln->idx)
	{
		if (g_editln->str.buf[--g_editln->idx] != '\n')
		{
			ft_puts(STDOUT_FILENO, TC_BA);
			--g_screen->col;
		}
		else
		{
			--g_editln->row;
			ch = *(uint16_t *)ft_vecat(&g_editln->cols,
				(size_t)(g_editln->row - 1));
			ft_puts(STDOUT_FILENO, TC_UP);
			ft_putf(STDOUT_FILENO, TC_GOTOCH(ch));
			g_screen->col = ch;
		}
	}
	return (YEP);
}

inline int	rl_editright(char const *prompt)
{
	(void)prompt;
	if (g_editln->idx != g_editln->str.len)
	{
		if (g_editln->str.buf[++g_editln->idx - 1] != '\n' &&
			g_screen->col + 1 < g_screen->width)
		{
			ft_puts(STDOUT_FILENO, TC_FO);
			++g_screen->col;
		}
		else
		{
			++g_editln->row;
			ft_puts(STDOUT_FILENO, TC_DO);
			ft_puts(STDOUT_FILENO, TC_GOTOCH0);
			g_screen->col = 0;
		}
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
