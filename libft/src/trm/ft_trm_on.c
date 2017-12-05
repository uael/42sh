/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:11 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:37:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "libft/trm.h"

inline void	ft_trm_on(t_trm *self)
{
	tcsetattr(self->out.u.file.fd, TCSADRAIN, &self->tty);
	ft_trm_puts(self, tgetstr("ti", NULL));
	ft_trm_puts(self, tgetstr("vi", NULL));
	ft_ostream_flush(&self->out);
	self->on = 1;
}

inline void	ft_trm_off(t_trm *self)
{
	tcsetattr(self->out.u.file.fd, TCSADRAIN, &self->tmp);
	ft_trm_puts(self, tgetstr("te", NULL));
	ft_trm_puts(self, tgetstr("ve", NULL));
	ft_ostream_flush(&self->out);
	self->on = 0;
}
