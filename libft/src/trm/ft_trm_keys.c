/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trm_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:11 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:37:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/trm.h"

#define TRK_ONEK(ch) ((ch)==9||(ch)==10||(ch)==32||(ch)==127||(ch)==27)

inline int		ft_trm_getch(t_trm *t)
{
	uint8_t	c[2];
	uint8_t	n;
	int		r;

	n = 0;
	ft_memset(c, 0, 2 * sizeof(char));
	while (42)
		if (!ft_du8_size(&t->in) &&
			((r = (int)read(t->out.u.file.fd, &c, 2)) < 0 ||
			(r > 0 && !ft_du8_pushnc(&t->in, c, (size_t)r))))
			return (ENO);
		else if (ft_du8_popn(&t->in, 2, c) <= 0)
			break ;
		else if ((n += r) == 1 && TRK_ONEK(c[0]))
			return (c[0]);
		else if (n == 2 && c[0] == 27 && c[1] == 91)
			continue ;
		else if (n == 4 && c[0] == 51 && c[1] == 126)
			return (c[1]);
		else if (n == 3 && (c[0] >= 65 && c[0] <= 68))
			return (c[0]);
		else
			break ;
	return (0);
}

inline t_sz		ft_trm_puts(t_trm *self, char const *s)
{
	return (ft_ostream_puts(&self->out, s));
}

inline ssize_t	ft_trm_putr(t_trm *self, char c, size_t n)
{
	char buf[(n * sizeof(char)) + 1];

	if (!n)
		return (0);
	ft_memset(buf, c, n);
	buf[n] = '\0';
	return (ft_trm_puts(self, buf));
}
