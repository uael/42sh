/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/env.h"

static t_ofs	g_cerr_stack = { STDERR_FILENO, 0, { 0 } };
static t_ofs	*g_cerr = &g_cerr_stack;

int			sh_verr(char const *fmt, va_list ap)
{
	ft_ofswrf(g_cerr, COLOR_BRED"ush: "COLOR_RESET);
	ft_ofsvwrf(g_cerr, fmt, ap);
	ft_ofsflush(g_cerr);
	return (WUT);
}

int			sh_err(char const *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	sh_verr(fmt, ap);
	va_end(ap);
	return (WUT);
}

int			sh_synerr(char const *ln, char const *it, char const *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	sh_verr(fmt, ap);
	va_end(ap);
	ft_ofswrc(g_cerr, '\n');
	if (ln)
	{
		ft_ofswrs(g_cerr, ln);
		if (!it)
			it = ft_strchr(ln, 0);
		while (++ln <= it)
			ft_ofswrc(g_cerr, ' ');
		ft_ofswrs(g_cerr, COLOR_BRED"^"COLOR_RESET"\n");
	}
	ft_ofsflush(g_cerr);
	return (WUT);
}
