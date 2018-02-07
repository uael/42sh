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

#include "ush/word.h"

#define DQUOT(IT) ft_strchr("\\\n\"$", *(IT))
#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))

inline size_t	sh_wordresolve(t_sds *d, char const *s, size_t n, uint8_t *e)
{
	t_bool	bs;
	char	quote;

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
		else
			*ft_sdspush(d) = *s++;
	return (d->len);
}


