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

#include "ush/word.h"
#include "ush/shell.h"

#define DQUOT(IT) ft_strchr("\\\n\"$", *(IT))
#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))

static size_t	getvar(char const *from, char *to)
{
	t_bool	bracket;
	char	*beg;

	beg = to;
	if ((bracket = (t_bool)(*from == '{')))
		++from;
	if (*from == '_' || ft_isalpha(*from))
		while (*from && (*from == '_' || ft_isalnum(*from)) &&
			(!bracket || *from != '}'))
			*to++ = *from++;
	else if (ft_isdigit(*from))
		while (*from && ft_isdigit(*from))
			*to++ = *from++;
	else if (ft_strchr("#?$!", *from))
		*to++ = *from;
	else
		return (0);
	*to = '\0';
	return (to - beg + (bracket ? 2 : 0));
}

static size_t	resolvevar(t_sds *word, char const *src)
{
	char	var[PATH_MAX];
	char	buf[20];
	char	*val;
	size_t	len;
	int		n;

	len = getvar(src, var);
	if ((val = sh_varget(var, g_env)))
		ft_sdsapd(word, val);
	else if (ft_isdigit(*var) && (n = (int)ft_atoi(var)) < g_sh->ac && n >= 0)
		ft_sdsapd(word, g_sh->av[n]);
	else if ((len == 1 && ft_strchr("#?$!", *var)))
	{
		if (*var == '#')
			n = g_sh->ac;
		else if (*var == '?')
			n = g_sh->status;
		else if (*var == '$')
			n = g_sh->pid;
		else if (*var == '!')
			n = ps_lastpid();
		ft_sdsmpush(word, buf, ft_intstr(buf, n, 10));
	}
	return (len);
}

inline size_t	sh_wordresolve(t_sds *d, char const *s, size_t n, uint8_t *e)
{
	t_bool	bs;
	char	quote;
	size_t	len;

	bs = 0;
	quote = 0;
	e ? (*e = 0) : 0;
	ft_sdsctor(d);
	while (n-- && *s)
		if (bs)
		{
			if (quote == '"')
				*ft_sdspush(d) = DQUOT(s) ? *s++ : (char)'\\';
			else if (quote == '\'')
				*ft_sdspush(d) = QUOTE(s) ? *s++ : (char)'\\';
			else
				*ft_sdspush(d) = *s++;
		}
		else if ((bs = (t_bool)(*s == '\\')))
			++s;
		else if (*s == '\'' || *s == '"' || *s == '`')
		{
			if ((quote = (char)(quote ? 0 : *s)) && e && *e)
				*e = 0;
			++s;
		}
		else if (*s == '$' && n && *s + 1 && (!quote || quote == '"'))
		{
			len = resolvevar(d, s + 1) + 1;
			len > n ? (n = 0) : (n -= len);
			s += len;
		}
		else
			*ft_sdspush(d) = *s++;
	return (d->len);
}


