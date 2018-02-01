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

static inline void	histback(char *not, t_bool *c)
{
	t_sds	*ln;

	ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 2, NULL);
	if ((ln = rl_histback()))
		ft_sdsmput(&g_eln->str, not - g_eln->str.buf, ln->buf, ln->len - 1);
	*c = 1;
}

static inline void	histat(char *not, t_bool *c)
{
	t_sds	*ln;
	int64_t i;
	size_t	l;

	if (*(not + 1) == '-' && !ft_isdigit(*(not + 2)))
		ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 2, NULL);
	else
	{
		i = ft_atoi(not + 1);
		l = ft_intlen(i, 10);
		ft_sdsnrem(&g_eln->str, not - g_eln->str.buf, 1 + l + (i < 0), NULL);
		if ((ln = rl_histat(i)))
			ft_sdsmput(&g_eln->str, not - g_eln->str.buf, ln->buf, ln->len - 1);
		*c = 1;
	}
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
	while ((not = ft_strchr(beg, '!')))
	{
		if (!ft_strlen(not))
			break ;
		if (*(not + 1) == '!')
			histback(not, &c);
		else if (*(not + 1) == '-' || ft_isdigit(*(not + 1)))
			histat(not, &c);
		beg = not + 1;
	}
	if (c)
	{
		g_eln->idx = g_eln->str.len;
		rl_editprint();
	}
	return (c ? YEP : NOP);
}
