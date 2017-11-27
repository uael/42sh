/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:25 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

inline t_ret	msh_bi_unsetenv(t_msh *self, t_vstr *av)
{
	t_ret	ret;

	if (av->len != 2)
		return (CMD_NOK("unsetenv: syntax error\nusage: unsetenv <key>"));
	if (!av->buf[1] || ft_strchr(av->buf[1], '='))
		return (CMD_NOK("unsetenv: syntax error\nusage: unsetenv <key>"));
	if ((ret = msh_unsetenv(self, av->buf[1])) == RET_ERR)
		return (RET_ERR);
	if (ret == RET_NOK)
		return (CMD_NOK("unsetenv: Environ not found"));
	return (RET_OK);
}
