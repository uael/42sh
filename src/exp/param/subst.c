/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/param/subst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libps.h>

#include "ush/exp.h"

static char g_num[21];

/*
** TODO: perform a real split, this one is shitty
*/

static void	splitvalue(t_sds *word, t_vec *av, t_param *p)
{
	char	*beg;
	char	*end;
	char	*next;
	int		i;

	beg = p->val;
	i = 0;
	while (i || *beg)
	{
		if (beg != p->val)
		{
			*(char **)ft_vecpush(av) = ft_strdup(word->buf);
			word->len = 0;
		}
		if (!i && !*(beg += ft_strspn(beg, g_ifsw)))
			break ;
		end = beg + ft_strcspn(beg, g_ifs);
		next = end + ft_strspn(end, g_ifsw);
		if ((i = (*next && ft_strchr(g_ifs, *next))))
			++next;
		*end = 0;
		ft_sdsapd(word, beg);
		beg = next;
	}
}

int			sh_expparamsubst(t_sds *word, char **words, t_vec *av, t_param *p)
{
	uint8_t	l;
	int		i;

	if (p->brace && **words != '}')
		return (sh_expparamdone(p, NOP));
	if ((i = sh_expparamval(word, words, av, p)))
		return (i);
	if (p->hash)
	{
		l = ft_intstr(g_num, (int64_t)(p->val ? ft_strlen(p->val) : 0), 10);
		ft_sdsmpush(word, g_num, l);
		return (sh_expparamdone(p, 2));
	}
	if (!p->val)
		return (sh_expparamdone(p, 2));
	if (p->quoted || !av)
		ft_sdsapd(word, p->val);
	else
	{
		p->freev ? 0 : (p->val = ft_strdup(p->val));
		p->freev = 1;
		splitvalue(word, av, p);
	}
	return (sh_expparamdone(p, 0));
}
