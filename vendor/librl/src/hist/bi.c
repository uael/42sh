/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist/bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hist.h"
#include "../edit.h"

static inline char	*histback(char *not, t_bool *c)
{
	t_sds	*ln;
	size_t	sz;

	ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 2, NULL);
	if ((ln = rl_histback()) && (ln->len - 1 + g_eln->str.len < UINT16_MAX))
	{
		sz = not - g_eln->str.buf;
		ft_sdsmput(&g_eln->str, sz, ln->buf, ln->len - 1);
		*c = 1;
		return (g_eln->str.buf + sz + ln->len);
	}
	return (not + 1);
}

static inline char	*histatc(char *not, t_bool *c)
{
	t_sds	*ln;
	int64_t i;
	size_t	l;
	size_t	sz;

	if (*(not + 1) == '-' && !ft_isdigit(*(not + 2)))
		ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 2, NULL);
	else
	{
		i = ft_atoi(not + 1);
		l = ft_intlen(i, 10);
		ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 1 + l + (i < 0), NULL);
		if ((ln = rl_histat(i)) && (ln->len - 1 + g_eln->str.len < UINT16_MAX))
		{
			sz = not - g_eln->str.buf;
			ft_sdsmput(&g_eln->str, sz, ln->buf, ln->len - 1);
			*c = 1;
			return (g_eln->str.buf + sz + ln->len);
		}
	}
	return (not + 1);
}

static inline char	*histat(char *not, ssize_t i, size_t rlen, t_bool *c)
{
	t_sds	*ln;
	size_t	sz;

	ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 1 + rlen, NULL);
	if ((ln = rl_histat(i)) && (ln->len - 1 + g_eln->str.len < UINT16_MAX))
	{
		sz = not - g_eln->str.buf;
		ft_sdsmput(&g_eln->str, sz, ln->buf, ln->len - 1);
		*c = 1;
		return (g_eln->str.buf + sz + ln->len);
	}
	return (not + 1);
}

static inline char	*histfind(char *not, t_bool *c)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	word[MAX_INPUT + 1];

	j = 1;
	i = 0;
	while (i <= MAX_INPUT && not[j] && !ft_strchr(" \t\n!", not[j]))
		word[i++] = not[j++];
	word[i] = '\0';
	l = i;
	if (g_hist_len)
	{
		i = g_hist_len;
		while (i > 0)
			if (ft_strstr((g_hist + --i)->buf, word))
				return (histat(not, i, l, c));
	}
	return (not + 1);
}

inline int			rl_histbi(void)
{
	char	*not;
	char	*beg;
	t_bool	c;

	if (!g_eln->str.len)
		return (NOP);
	beg = g_eln->str.buf;
	c = 0;
	while (beg && *beg && (not = ft_strchr(beg, '!')))
	{
		if (!ft_strlen(not))
			break ;
		if (*(not + 1) == '!')
			beg = histback(not, &c);
		else if (*(not + 1) == '-' || ft_isdigit(*(not + 1)))
			beg = histatc(not, &c);
		else if (!*(not + 1))
			return (YEP);
		else
			beg = histfind(not, &c);
	}
	if (c && (g_eln->idx = g_eln->str.len) > 0)
		rl_editprint();
	return (c ? YEP : NOP);
}
