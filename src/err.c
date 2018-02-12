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
#include "ush/lex.h"

static t_ofs	g_cerr_stack = { STDERR_FILENO, 0, { 0 } };
static t_ofs	*g_cerr = &g_cerr_stack;

int				sh_verr(char const *fmt, va_list ap)
{
	if (isatty(STDERR_FILENO))
		ft_ofswrf(g_cerr, COLOR_BRED"ush: "COLOR_RESET);
	else
		ft_ofswrf(g_cerr, "ush: ");
	ft_ofsvwrf(g_cerr, fmt, ap);
	ft_ofsflush(g_cerr);
	return (WUT);
}

int				sh_err(char const *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	sh_verr(fmt, ap);
	va_end(ap);
	return (WUT);
}

static void		printline(char const *ln, char const *it)
{
	char const	*b;
	char const	*e;

	if (!*it)
		--it;
	b = ft_strrschr(ln, it, '\n');
	if (!b)
		b = ln;
	e = ft_strchr(it, '\n');
	if (!e)
		e = ft_strchr(it, '\0');
	if (b == e && ln < it)
	{
		b = ft_strrschr(ln, it - 1, '\n');
		if (!b)
			b = ln;
	}
	if (b < e && *b == '\n')
		++b;
	ft_ofswr(g_cerr, b, e - b);
	ft_ofswrc(g_cerr, '\n');
	while (++b <= it)
		ft_ofswrc(g_cerr, ' ');
	ft_ofswrs(g_cerr, isatty(STDERR_FILENO) ? COLOR_BRED"^"COLOR_RESET"\n"
		: "^\n");
}

int				sh_synerr(char const *ln, char const *it, char const *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	sh_verr(fmt, ap);
	va_end(ap);
	ft_ofswrc(g_cerr, '\n');
	if (ln)
		printline(ln, it);
	ft_ofsflush(g_cerr);
	return (OUF);
}

int				sh_evalerr(char const *ln, t_tok *tok, char const *fmt, ...)
{
	va_list		ap;
	char		*it;

	va_start(ap, fmt);
	sh_verr(fmt, ap);
	va_end(ap);
	ft_ofswrc(g_cerr, '\n');
	if (ln)
	{
		if (!tok)
			it = ft_strchr(ln, 0);
		else
			it = (char *)(ln + tok->pos);
		printline(ln, it);
	}
	ft_ofsflush(g_cerr);
	return (OUF);
}
