/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys/backspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:06:07 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/keys.h"

inline int	sh_keys_backspace(t_sh *self, t_tc *tc)
{
	(void)self;
	if (tc->c && (tc_left(tc) || tc_delc(tc)))
		return (WUT);
	return (YEP);
}
