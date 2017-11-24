/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:13 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline t_ret	msh_bi_setenv(t_msh *self, t_vstr *av)
{
	if (av->len != 3)
		return (CMD_NOK("setenv: syntax error\nusage: setenv <key> <value>"));
	if (!av->buf[1] || ft_strchr(av->buf[1], '=') ||
		!av->buf[2] || ft_strchr(av->buf[2], '='))
		return (CMD_NOK("setenv: syntax error\nusage: setenv <key> <value>"));
	return (msh_setenv(self, av->buf[1], av->buf[2]));
}
