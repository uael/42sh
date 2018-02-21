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

static char		*g_sstr;
static size_t	g_slen;
static t_vec	g_sav;

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

static void		expsuffix(char **words, t_vec *sav, char **sstr, size_t *slen)
{
	t_sds swrd;

	ft_vecctor(sav, sizeof(char *));
	ft_sdsctor(&swrd);
	sh_exp(words, &swrd, sav);
	if (swrd.len)
		*(char **)ft_vecpush(sav) = swrd.buf;
	else
		ft_sdsdtor(&swrd);
	if (sav->len)
	{
		*sstr = *(char **)ft_vecbeg(sav);
		*slen = ft_strlen(*sstr);
	}
}

static int		expbrace(int *r, t_sds *word, t_vec *av)
{
	char	buf[21];
	char	*value;
	uint8_t	l;
	size_t	j;

	while (r[0] <= r[1])
	{
		l = ft_intstr(buf, r[0], 10);
		buf[l] = '\0';
		value = ft_malloc(word->len + l + g_slen + 1);
		ft_bzero(value, word->len + l + g_slen + 1);
		if (word->len)
			ft_strcat(value, word->buf);
		ft_strcat(value, buf);
		if (g_slen)
			ft_strcat(value, g_sstr);
		*(char **)ft_vecpush(av) = value;
		j = 0;
		while (++j < g_sav.len)
			*(char **)ft_vecpush(av) = ft_strdup(*(char **)ft_vecat(&g_sav, j));
		r[0] += r[2];
	}
	word->len = 0;
	ft_vecdtor(&g_sav, (t_dtor)ft_pfree);
	return (YEP);
}

int				sh_expbrace(t_sds *word, char **words, t_vec *av)
{
	int i;
	int r[3];
	int s[3];

	i = 1;
	if (!ft_isdigit(*(*words + i)) && *(*words + i) != '-' &&
		*(*words + i) != '+')
		return (sh_expglob(word, words, av));
	ft_bzero(r, 3 * sizeof(int));
	ft_memset(s, 0, 3 * sizeof(int));
	if ((i = exprange(r, s, *words)) == 0)
		return (sh_expglob(word, words, av));
	s[0] ? (r[0] *= s[0]) : 0;
	s[1] ? (r[1] *= s[1]) : 0;
	r[2] ? 0 : (r[2] = 1);
	g_slen = 0;
	g_sstr = NULL;
	if (*(*words += i + 1))
		expsuffix(words, &g_sav, &g_sstr, &g_slen);
	--*words;
	return (expbrace(r, word, av));
}
