/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok/expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/tok.h"

static t_tok	tokapd(uint16_t pos, char *beg, char *end)
{
	t_tok tok;

	ft_memset(&tok, 0, sizeof(t_tok));
	ft_sdsmpush((t_sds *)&tok, beg, end - beg);
	tok.id = TOK_WORD;
	tok.pos = pos;
	return (tok);
}

inline void		sh_tokexplode(t_tok *tok, t_vec *av)
{
	char		*val;
	char		*end;
	size_t		i;
	uint16_t	pos;

	while (tok->len && (ft_strchr(sh_varifs(), *tok->val) || ISREOL(tok->val)))
		ft_sdssht((t_sds *)tok, NULL);
	val = tok->val;
	while (*val && !ft_strchr(sh_varifs(), *val) && !ISREOL(val))
		++val;
	if (!*val || (*val = '\0'))
		return ;
	tok->len = val++ - tok->val;
	pos = tok->pos;
	i = 0;
	while (*val)
		if (ft_strchr(sh_varifs(), *val) || ISREOL(val))
			++val;
		else if (*(end = val))
		{
			while (*end && !ft_strchr(sh_varifs(), *end) && !ISREOL(end))
				++end;
			*(t_tok *)ft_deqput(into, ++i) = tokapd(pos, val, end);
			val = end;
		}
}

inline t_sds	*sh_tokdexpand(t_sds *dst, t_tok *src, char *ln)
{

}

inline size_t	sh_tokexpand(char *dst, t_tok *src, char *ln, size_t n)
{

}
