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
	size_t	i;

	if (av->len < 2)
		return (CMD_NOK("unset: syntax error\nusage: unset [keys...]"));
	i = 0;
	while (++i < av->len)
		if (ft_strchr(av->buf[i], '='))
			return (CMD_NOK("unset: syntax error\nusage: unset [keys...]"));
		else if ((ret = msh_unsetenv(self, av->buf[i])) == RET_ERR)
			return (RET_ERR);
		else if (ret == RET_NOK)
			ft_putl(2, "unset: Environ not found");
	return (RET_OK);
}
