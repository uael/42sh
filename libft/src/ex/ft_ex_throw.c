/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex/ft_ex_throw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:27:49 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 12:56:41 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ex.h"

#include "libft/io.h"
#include "libft/fs.h"

int		ft_ex_throw(int rcode)
{
	t_ex_hdl *hdl;

	if ((hdl = ft_ex_get(errno)))
		return (hdl->cb(rcode, hdl->arg));
	if (errno == ENOMEM)
		exit(rcode);
	if (errno == ENIMPL)
	{
		ft_putf(2, COLOR_RED COLOR_BOLD"error: "COLOR_RESET"%e\n", errno);
		exit(rcode);
	}
	return (rcode);
}

int		ft_eno_throw(int rcode, int eno)
{
	errno = eno;
	return (ft_ex_throw(rcode));
}
