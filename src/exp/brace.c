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

static int		parsevalue(t_range *range, int *rr, int *ss, char c)
{
	if (c == '-' || c == '+')
	{
		if (*rr || *ss)
			return (1);
		*ss = c == '-' ? -1 : 1;
	}
	else if (ft_isalpha(c))
	{
		if (*rr || *ss || rr == range->range + 2)
			return (1);
		*rr = c;
		range->ascii = 1;
	}
	else if (ft_isdigit(c))
	{
		if (range->ascii && rr != range->range + 2)
			return (1);
		*rr = *rr * 10 + c - '0';
	}
	else
		return (0);
	return (2);
}

static int		parserange(t_range *range, int *r, int *s, char *words)
{
	int *rr;
	int *ss;
	int i;
	int st;

	i = 0;
	rr = r;
	ss = s;
	while (words[++i])
		if ((st = parsevalue(range, rr, ss, words[i])))
		{
			if (st == 1)
				return (0);
		}
		else if (words[i] == '.')
		{
			if (words[i + 1] != '.' || rr - r >= 2)
				return (0);
			(void)(++i && ++rr && ++ss);
		}
		else if (words[i] == '}')
			break ;
		else
			return (0);
	return ((!words[i] || rr - r < 1 || (rr - r == 2 && !r[2])) ? 0 : i);
}

static void		expvalue(t_range *r, t_sds *val, t_sds *word)
{
	char	buf[21];
	uint8_t	l;

	if (word->len)
		ft_sdsapd(val, word->buf);
	if (r->ascii)
		*ft_sdspush(val) = (char)(r->range[0] == '\\' ? ' ' : r->range[0]);
	else
	{
		l = ft_intstr(buf, r->range[0], 10);
		buf[l] = '\0';
		ft_sdsapd(val, buf);
	}
}

static int		expbrace(t_range *r, t_sds *word, t_vec *av)
{
	size_t	j;
	t_sds	v;
	int		d;

	d = r->range[0] > r->range[1];
	ft_sdsctor(&v);
	while (d ? r->range[0] >= r->range[1] : r->range[0] <= r->range[1])
	{
		expvalue(r, &v, word);
		j = 0;
		if (!r->av.len)
			*(char **)ft_vecpush(av) = ft_strdup(v.buf);
		else
			while (j < r->av.len)
				*(char **)ft_vecpush(av) =
					ft_strjoin(v.buf, *(char **)ft_vecat(&r->av, j++));
		v.len = 0;
		r->range[0] += r->range[2];
	}
	word->len = 0;
	ft_vecdtor(&r->av, (t_dtor)ft_pfree);
	ft_sdsdtor(&v);
	return (YEP);
}

int				sh_expbrace(t_sds *word, char **w, t_vec *av)
{
	int		i;
	int		s[3];
	t_range	r;
	t_sds	swrd;

	i = 1;
	if (!ft_isalnum(*(*w + i)) && *(*w + i) != '-' && *(*w + i) != '+')
		return (sh_expglob(word, w, av));
	ft_bzero(&r, sizeof(t_range));
	ft_memset(s, 0, 3 * sizeof(int));
	if ((i = parserange(&r, r.range, s, *w)) == 0)
		return (sh_expglob(word, w, av));
	s[0] ? (r.range[0] *= s[0]) : 0;
	s[1] ? (r.range[1] *= s[1]) : 0;
	r.range[2] ? 0 : (r.range[2] = 1);
	r.range[0] > r.range[1] && r.range[2] ? (r.range[2] *= -1) : 0;
	if (*(*w += i + 1))
	{
		ft_vecctor(&r.av, sizeof(char *));
		ft_sdsctor(&swrd);
		sh_exp(w, &swrd, &r.av);
		swrd.len ? (*(char **)ft_vecpush(&r.av) = swrd.buf) : ft_sdsdtor(&swrd);
	}
	--*w;
	return (expbrace(&r, word, av));
}
