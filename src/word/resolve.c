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

#include "ush/eval.h"
#include "ush/shell.h"
#include "ush/word.h"

#define DQUOT(IT) ft_strchr("\\\n\"$", *(IT))
#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))

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

static inline t_bool	inhib(t_sds *d, char quote, char const **s, size_t *n)
{
	if ((quote == '"' && !DQUOT(*s)) || (quote == '\'' && !QUOTE(*s)))
		*ft_sdspush(d) = (char)'\\';
	else
	{
		*ft_sdspush(d) = *(*s)++;
		--*n;
		return (1);
	}
	return (0);
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
	while (*n && **s != '`' && **s)
		if (!(bs ^= 1))
			inhib(&cmd, '`', s, n);
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
	uint8_t *e)
{
	t_bool	bs;
	char	q;
	size_t	len;

	bs = 0;
	q = 0;
	e ? (*e = 1) : 0;
	ft_sdsctor(d);
	while (n && *s)
		if (!(bs ^= 1))
			inhib(d, q, &s, &n) && e ? (*e = 0) : 0;
		else if ((bs = (t_bool)(*s == '\\')))
			(void)(++s && --n);
		else if (*s == '\'' || *s == '"')
			onquote(d, &q, &s, &n) && e ? (*e = 0) : 0;
		else if (*s == '`' && n && *(s + 1) && (!q || q == '"'))
			onbquote(d, &s, &n);
		else if (*s == '$' && n && *(s + 1) && (!q || q == '"'))
		{
			s += (len = sh_varexpand(d, s + 1) + 1);
			len > n ? (n = 0) : (n -= len);
		}
		else if ((*ft_sdspush(d) = *s++))
			--n;
	return (d->len);
}
