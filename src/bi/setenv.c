/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:13 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"
#include "msh/env.h"

inline t_ret	msh_bi_setenv(t_msh *self, t_vstr *av)
{
	if (av->len == 1)
		return (msh_bi_env(self, av));
	if (av->len < 2 || av->len > 3 || !av->buf[1] ||
		ft_strchr(av->buf[1], '=') ||
		(av->len == 3 && ft_strchr(av->buf[2], '=')))
		return (CMD_NOK("setenv: syntax error\nusage: setenv key [value]"));
	if (!ft_isalpha(*av->buf[1]))
		return (CMD_NOK("setenv: not an identifier\n"
			"usage: setenv key [value]"));
	return (msh_setenv(self, av->buf[1], av->len == 3 ? av->buf[2] : NULL));
}
