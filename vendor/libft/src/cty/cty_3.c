/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cty_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 11:11:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cty.h"
#include "libft/mem.h"
#include "libft/int.h"
#include "libft/str.h"

inline int	ft_iscntrl(int c)
{
	return (c < 32 || c == 127);
}

inline int	ft_iscoolc(int c)
{
	return (ft_isspace(c) || ft_isprint(c));
}

inline char	*ft_toprint(int c, char *buf)
{
	if (!buf)
		buf = ft_calloc(20 * sizeof(char));
	if (c == ' ')
		ft_strcpy(buf, "<space>");
	else if (ft_isprint(c))
		buf[0] = (char)c;
	else if (c == '\n')
		ft_strcpy(buf, "<newline>");
	else if (c == '\f')
		ft_strcpy(buf, "<space>");
	else if (c == '\t')
		ft_strcpy(buf, "<tab>");
	else if (c == '\r')
		ft_strcpy(buf, "<carriage>");
	else if (c == -1)
		ft_strcpy(buf, "<EOF>");
	else
		ft_intstr(buf, c, 10);
	return (buf);
}
