/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist/load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hist.h"

inline int		rl_histload(char const *filename)
{
	t_ifs	in;
	ssize_t	sz;
	char	*ln;
	t_bool	new;

	if (ft_ifsopen(&in, filename))
		return (NOP);
	in.lim = UINT16_MAX;
	new = 1;
	ln = NULL;
	while ((sz = ft_ifschr(&in, 0, '\n', &ln)) > 0)
	{
		if (sz == 1)
			new = 1;
		else if (sz < UINT16_MAX)
		{
			if (!ft_stris((new ? rl_histadd(ln, (size_t)sz) : rl_histcat(ln,
				(size_t)sz, 0, 0)), ft_iscoolc))
				return (WUT);
			new = 0;
		}
		ft_ifsrd(&in, NULL, (size_t)sz);
	}
	ft_ifsclose(&in);
	return (YEP);
}
