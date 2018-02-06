/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word/expand.c                                      :+:      :+:    :+:   */
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

static size_t	getvar(char *from, char *to)
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

static size_t	expandn(t_sds *word, size_t from, int n)
{
	char	buf[20];
	size_t	l;

	l = ft_intstr(buf, n, 10);
	ft_sdsmput(word, from - 1, buf, l);
	return (l);
}

static size_t	expandspecial(t_sds *word, char *var, size_t from)
{
	int		i;
	size_t	len;

	len = 0;
	if (ft_isdigit(*var) && (i = (int)ft_atoi(var)) < g_sh->ac && i >= 0)
		ft_sdsmput(word, from - 1, g_sh->av[i], len = ft_strlen(g_sh->av[i]));
	else if (*var == '#')
		len = expandn(word, from, g_sh->ac);
	else if (*var == '?')
		len = expandn(word, from, g_sh->status);
	else if (*var == '$')
		len = expandn(word, from, g_sh->pid);
	else if (*var == '!')
		len = expandn(word, from, ps_lastpid());
	return (len);
}

static char		*expandvar(t_sds *word, size_t from)
{
	char	var[PATH_MAX];
	char	*val;
	size_t	len;

	if ((len = getvar(word->buf + from, var)))
	{
		ft_sdsnrem(word, from - 1, len + 1, NULL);
		if ((val = sh_varget(var, g_env)))
			ft_sdsmput(word, from - 1, val, len = ft_strlen(val));
		else if (ft_isdigit(*var) || (len == 1 && ft_strchr("#?$!", *var)))
			len = expandspecial(word, var, from);
		else
			len = 0;
		return (word->buf + from - 1 + len);
	}
	return (word->buf + from);
}

inline int		sh_wordexpand(t_sds *word)
{
	char	*dollar;
	char	*beg;

	beg = word->buf;
	while ((dollar = ft_strchr(beg, '$')))
	{
		if (!((word->buf + word->len) - dollar))
			break ;
		else
			beg = expandvar(word, ++dollar - word->buf);
	}
	return (beg != word->buf);
}
