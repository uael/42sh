/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_dtor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline void	ft_dstr_dtor(t_dstr *self, t_dtor idtor)
{
	char	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_dstr_begin(self);
			while (item != ft_dstr_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_dstr);
}
