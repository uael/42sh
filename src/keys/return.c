/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys/return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:06:07 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/keys.h"

inline int	sh_keys_return(t_sh *self, t_tc *tc)
{
	t_src	src;

	ft_dstr_pushc(&tc->in, '\n');
	if (tc_down(tc) || tc_margin_left(tc))
		return (WUT);
	if (!tc->in.len || !(self->ln = ft_strdup(tc->in.buf)))
		return (NOP);
	if (tc_clrln(tc))
		return (WUT);
	tc_pause(tc);
	ft_src_init_str(&src, self->ln);
	ft_lexer_unshift(&self->lexer, &src);
	if (!ft_vstr_size(&self->history) ||
		ft_strcmp(*(ft_vstr_end(&self->history) - 1), self->ln))
	{
		ft_vstr_pushc(&self->history, self->ln);
		while (ft_vstr_size(&self->history) > 100)
			ft_vstr_shift(&self->history, NULL);
	}
	self->cursor = ft_vstr_size(&self->history);
	return (sh_eval(self) < 0 ? WUT : NOP);
}
