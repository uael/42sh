/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex/ex_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:27:49 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:38:54 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ex.h"

#include "libft/io.h"
#include "libft/fs.h"

int		ft_throw(int rcode, char const *fn, int line)
{
	t_ex_hdl *hdl;

	if (fn && errno != EBADF && errno != EIO)
		ft_putf(2, "In function: "COLOR_BOLD"'%s:%d':\n"COLOR_RESET, fn, line);
	if ((hdl = ft_exget(errno)))
		return (hdl->cb(rcode, hdl->arg));
	if (errno == ENOMEM)
		exit(rcode);
	if (errno == ENIMPL)
	{
		ft_putf(2, COLOR_BRED"error: "COLOR_RESET"%e\n", errno);
		exit(rcode);
	}
	return (rcode);
}

int		ft_ethrow(int rcode, int eno, char const *msg, int line)
{
	errno = eno;
	return (ft_throw(rcode, msg, line));
}
