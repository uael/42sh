/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 07:40:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_keys_hdl	g_hdls[] =
{
	{K_BACKSPACE, sh_keys_backspace},
	{K_DELETE, sh_keys_delete},
	{K_DOWN, sh_keys_down},
	{K_LEFT, sh_keys_left},
	{K_RETURN, sh_keys_return},
	{K_RGT, sh_keys_right},
	{K_UP, sh_keys_up},
	{NULL, NULL}
};

inline int			sh_keys(t_tc *tc, char *in)
{
	t_sh		*sh;
	t_keys_hdl	*hdl;

	sh = tc->arg;
	hdl = g_hdls;
	while (hdl->key)
	{
		if (ft_strcmp(hdl->key, in) == 0)
			return (hdl->cb(sh, tc));
		++hdl;
	}
	return (tc_puts(tc, in));
}
