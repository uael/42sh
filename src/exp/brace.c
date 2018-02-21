/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/brace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

static int		exprange(int *r, int *s, char *words)
{
	int *rr;
	int *ss;
	int i;

	i = 0;
	rr = r;
	ss = s;
	while (words[++i])
		if ((words[i] == '-' || words[i] == '+') && (*rr || *ss))
			return (0);
		else if (words[i] == '-' || words[i] == '+')
			*ss = words[i] == '-' ? -1 : 1;
		else if (ft_isdigit(words[i]))
			*rr = *rr * 10 + words[i] - '0';
		else if (words[i] == '.')
		{
			if (words[i + 1] != '.' || rr - r >= 3)
				return (0);
			(void)(++i && ++rr && ++ss);
		}
		else if (words[i] == '}')
			break ;
		else
			return (0);
	return ((!words[i] || rr - r < 1 || (rr - r == 2 && !r[2])) ? 0 : i);
}

static void		expsuffix(char **words, t_vec *sav)
{
	t_sds swrd;

	ft_vecctor(sav, sizeof(char *));
	ft_sdsctor(&swrd);
	sh_exp(words, &swrd, sav);
	if (swrd.len)
		*(char **)ft_vecpush(sav) = swrd.buf;
	else
		ft_sdsdtor(&swrd);
}

static void		expvalue(t_range *r, t_sds *val, t_sds *word)
{
	char	buf[21];
	uint8_t	l;

	l = ft_intstr(buf, r->range[0], 10);
	buf[l] = '\0';
	if (word->len)
		ft_sdsapd(val, word->buf);
	ft_sdsapd(val, buf);
}

static int		expbrace(t_range *r, t_sds *word, t_vec *av)
{

	size_t	j;
	t_sds	v;

	ft_sdsctor(&v);
	while (r->range[0] <= r->range[1])
	{
		expvalue(r, &v, word);
		j = 0;
		if (!r->av.len)
			*(char **)ft_vecpush(av) = ft_strdup(v.buf);
		else
			while (j < r->av.len)
				*(char **)ft_vecpush(av) =
					ft_strjoin(v.buf, *(char **)ft_vecat(&r->av, j++));
		r->range[0] += r->range[2];
		v.len = 0;
	}
	word->len = 0;
	ft_vecdtor(&r->av, (t_dtor)ft_pfree);
	ft_sdsdtor(&v);
	return (YEP);
}

int				sh_expbrace(t_sds *word, char **words, t_vec *av)
{
	int		i;
	int		s[3];
	t_range	range;

	i = 1;
	if (!ft_isdigit(*(*words + i)) && *(*words + i) != '-' &&
		*(*words + i) != '+')
		return (sh_expglob(word, words, av));
	ft_bzero(&range, sizeof(t_range));
	ft_memset(s, 0, 3 * sizeof(int));
	if ((i = exprange(range.range, s, *words)) == 0)
		return (sh_expglob(word, words, av));
	s[0] ? (range.range[0] *= s[0]) : 0;
	s[1] ? (range.range[1] *= s[1]) : 0;
	range.range[2] ? 0 : (range.range[2] = 1);
	if (*(*words += i + 1))
		expsuffix(words, &range.av);
	--*words;
	return (expbrace(&range, word, av));
}
