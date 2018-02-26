/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist/save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hist.h"

inline int		rl_histsave(char const *filename)
{
	t_sds	*line;
	t_ofs	*out;
	char	*beg;
	char	*eol;
	uint8_t	i;

	if (ft_ofstrunc(out = alloca(sizeof(t_ifs)), filename))
		return (ft_throw(WUT, FT_DBG));
	i = 0;
	ft_sdsctor(line = alloca(sizeof(t_sds)));
	while (rl_histcpy(i++, line))
	{
		beg = line->buf;
		while ((eol = ft_strchr(beg, '\n')))
		{
			ft_ofswr(out, beg, eol - beg);
			ft_ofswrc(out, '\n');
			beg = eol + 1;
		}
		ft_ofswrf(out, "%s\n\n", beg);
	}
	ft_sdsdtor(line);
	return (ft_ofsclose(out));
}
