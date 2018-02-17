/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word/resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libps.h>

#include "ush/shell.h"
#include "ush/eval.h"

#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))
#define MAGIC "?{[]}*!^"

static uint8_t			g_flags;

static inline int		subshell(char *ln)
{
	t_scope	*sh;
	int		st;
	char	*it;

	sh = g_sh;
	sh_scope();
	ft_memcpy(g_sh, sh, sizeof(t_scope));
	it = ln;
	while (!sh_lex(-1, &it, &ln, sh_eval))
		;
	st = g_sh->status;
	sh_unscope();
	return (sh_exit(st, NULL));
}

static inline void		onbslash(t_sds *d, char quote, char const **s,
	size_t *n)
{
	if ((quote == '"' && !ft_strchr("\\\n\"$", **s)) ||
		(quote == '\'' && !QUOTE(*s)))
		*ft_sdspush(d) = (char)'\\';
	else if (quote != '\'' && ft_strchr("\\"MAGIC, **s))
		*ft_sdspush(d) = (char)'\\';
	else
	{
		*ft_sdspush(d) = *(*s)++;
		--*n;
		g_flags &= ~WORD_EXPLODE;
	}
}

static inline int		onquote(t_sds *d, char *q, char const **s, size_t *n)
{
	if (*q && *q == **s)
		*q = 0;
	else if (!*q)
		*q = **s;
	else
		*ft_sdspush(d) = **s;
	++*s;
	--*n;
	if (*q)
	{
		g_flags &= ~WORD_EXPLODE;
		g_flags |= *q == '"' ? WORD_DQUOTE : WORD_SQUOTE;
	}
	return (*q);
}

static inline void		onbquote(t_sds *d, char const **s, size_t *n)
{
	t_sds		cmd;
	t_bool		bs;

	ft_sdsctor(&cmd);
	++*s;
	--*n;
	bs = 0;
	g_flags |= WORD_BQUOTE;
	while (*n && **s != '`' && **s)
		if (!(bs ^= 1))
			onbslash(&cmd, '`', s, n);
		else if ((bs = (t_bool)(**s == '\\')))
			(void)(++*s && --*n);
		else if ((*ft_sdspush(&cmd) = *(*s)++))
			--*n;
	if (cmd.len)
		ps_read(d, (t_proccb *)subshell, (t_dtor)free, cmd.buf);
	++*s;
	--*n;
}

inline size_t			sh_wordresolve(t_sds *d, char const *s, size_t n,
	uint8_t *flags)
{
	t_bool	bs;
	char	quote;
	size_t	len;

	bs = 0;
	g_flags = WORD_EXPLODE;
	ft_memset(d, quote = 0, sizeof(t_sds));
	while (n && *s)
		if (!(bs ^= 1))
			onbslash(d, quote, &s, &n);
		else if ((bs = (t_bool)(*s == '\\')))
			(void)(++s && --n);
		else if (*s == '\'' || *s == '"')
			onquote(d, &quote, &s, &n);
		else if (*s == '`' && n && *(s + 1) && (!quote || quote == '"'))
			onbquote(d, &s, &n);
		else if (*s == '$' && n && *(s + 1) && (!quote || quote == '"'))
		{
			s += (len = sh_varexpand(d, s + 1) + 1);
			len > n ? (n = 0) : (n -= len);
		}
		else
		{
			if (!quote && '\\' ==  *s)
				*ft_sdspush(d) = '\\';
			else if (quote && ft_strchr(MAGIC, *s))
				*ft_sdspush(d) = '\\';
			*ft_sdspush(d) = *s++;
			--n;
		}
	flags ? (*flags = g_flags) : 0;
	return (d->len);
}
