/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist/op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hist.h"

inline void		rl_histdel(size_t nb)
{
	if (nb < g_hist_len)
	{
		ft_sdsdtor(g_hist + nb);
		if (--g_hist_len)
			ft_memmove(g_hist + nb, g_hist + nb + 1,
				g_hist_len * sizeof(t_sds));
	}
}

inline t_sds	*rl_histat(ssize_t idx)
{
	if (idx >= HIST_MAX || idx <= -HIST_MAX)
		return (NULL);
	if (idx < 0 && g_hist_len - idx > 0)
		return (g_hist + g_hist_len + idx - 1);
	if (idx < g_hist_len)
		return (g_hist + idx);
	return (NULL);
}

inline t_sds	*rl_histback(void)
{
	if (g_hist_len)
		return (g_hist + g_hist_len - 1);
	return (NULL);
}
