/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 14:39:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib.h"
#include "libft/io.h"

inline void	ft_pfree(void **ptr)
{
	if (!ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

int			ft_dtor(int code, t_dtor dtor, void *arg, char const *msg, ...)
{
	va_list	ap;

	if (dtor && arg)
		(*dtor)(arg, NULL);
	if (!msg)
		return (code);
	va_start(ap, msg);
	ft_vputf(code ? 2 : 1, msg, ap);
	va_end(ap);
	return (code);
}

int			ft_exit(int code, t_dtor dtor, void *arg, char const *msg, ...)
{
	va_list	ap;

	if (dtor && arg)
		(*dtor)(arg, NULL);
	if (!msg)
		exit(code);
	va_start(ap, msg);
	ft_vputf(code ? 2 : 1, msg, ap);
	va_end(ap);
	exit(code);
}

int			ft_ret(int code, char const *msg, ...)
{
	va_list	ap;

	if (!msg)
		return (code);
	va_start(ap, msg);
	ft_vputf(code ? 2 : 1, msg, ap);
	va_end(ap);
	return (code);
}

int			ft_szret(int code, char const *msg, ...)
{
	va_list	ap;

	if (!msg)
		return (code);
	va_start(ap, msg);
	ft_vputf(code <= 0 ? 2 : 1, msg, ap);
	va_end(ap);
	return (code);
}
