/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofs_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:02:13 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

inline ssize_t	ft_ofswr(t_ofs *self, void const *buf, size_t n)
{
	uint8_t const	*cbuf;
	ssize_t			sz;

	cbuf = buf;
	sz = 0;
	while (n)
	{
		if (ft_ofswrc(self, *cbuf++))
			return (WUT);
		++sz;
		--n;
	}
	return (sz);
}

ssize_t			ft_ofswrs(t_ofs *self, char const *buf)
{
	return (ft_ofswr(self, buf, ft_strlen(buf)));
}

ssize_t			ft_ofswrl(t_ofs *self, long i, uint8_t base)
{
	char buf[21];

	return (ft_ofswr(self, buf, ft_intstr(buf, i, base)));
}

ssize_t			ft_ofswrul(t_ofs *self, unsigned long i, uint8_t base)
{
	char buf[21];

	return (ft_ofswr(self, buf, ft_uintstr(buf, i, base)));
}

ssize_t			ft_ofswrd(t_ofs *self, double i, int precision, uint8_t base)
{
	char buf[21];

	return (ft_ofswr(self, buf, ft_floatstr(buf, i, precision, base)));
}
