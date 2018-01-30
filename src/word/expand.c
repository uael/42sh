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

#include "ush/word.h"
#include "ush/shell.h"

static size_t	getvar(char *from, char *to)
{
	t_bool bracket;

	if ((bracket = (t_bool)(*from == '{')))
		++from;
	if (ft_isalpha(*from))
		while (*from && ft_isalnum(*from) && (!bracket || *from != '}'))
			*to++ = *from++;
	else if (ft_isdigit(*from))
		while (ft_isdigit(*from))
			*to++ = *from++;
	else if (ft_strchr())
		*to++ = *from++;

}

static char		*expandvar(t_sds *word, size_t from)
{
	char		*var;
	char		*end;
	char		name[PATH_MAX];
	char		*nptr;
	t_bool		bracket;

	var = word->buf + from;
	while (*(var - 1) != '$')
		++var;
	if ((bracket = (t_bool)(*var == '{')))
		++var;
	end = var;
	nptr = name;
	while (*end)
	{
		if ((bracket && *end == '}') || !ft_isalnum(*end))
			break ;
		*nptr++ = *end++;
	}
	*nptr = '\0';
	word->len = from;
	if ((end = sh_varget(var, g_env)))
		ft_sdsapd(word, end);
	else
		word->buf[from] = '\0';
	return (NULL);
}

inline void		sh_wordexpand(t_sds *word)
{
	char	*dollar;
	char	*beg;
	size_t	len;

	beg = word->buf;
	while ((dollar = ft_strchr(beg, '$')))
	{
		len = (word->buf + word->len) - dollar;
		if (dollar > word->buf && *(dollar - 1) == '\\')
		{
			ft_sdsrem(word, (dollar - word->buf) - 1, NULL);
			beg = word->buf + (dollar - word->buf);
		}
		else if (!len)
			break ;
		else
			beg = expandvar(word, ++dollar - word->buf);
	}
}
