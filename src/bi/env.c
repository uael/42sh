/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:31:34 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

#define ENV_I (1 << 0)

static t_st	env_parse_opts(t_vstr *av, uint8_t *opts)
{
	(void)av;
	(void)opts;
	return (OK);
}

inline t_st	sh_bi_env(t_sh *self, t_vstr *av)
{
	size_t	i;
	uint8_t	opts;

	(void)self;
	opts = 0;
	env_parse_opts(av, &opts);
	if (av->len != 1)
		return (ft_ret(NOK, "%s: %e\n", "env", E2BIG));
	i = 0;
	while (i < self->env.len)
		if (self->env.buf[i++])
			ft_putl(1, self->env.buf[i - 1]);
	return (OK);
}
