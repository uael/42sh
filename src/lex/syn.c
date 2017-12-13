/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/syn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline int				sh_lex_syn(t_tok *tok, char peek, t_src *src)
{
	ssize_t sz;

	while (peek == ' ' || peek == '\t')
	{
		ft_src_getc(src, NULL, &peek);
	}
	if (ft_strchr("=!()-;[]{|}\n", peek))
	{
		tok->val = NULL;
		tok->id = (uint8_t)peek;
		if ((sz = ft_src_next(src, NULL, 1)) <= 0)
			return (sz < 0 ? WUT : NOP);
		return (YEP);
	}
	return (NOP);
}
