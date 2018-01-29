/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

inline int		sh_lexnext(int fd, t_deq *toks, char c, char **ln)
{
	char	*it;
	int		st;

	if (fd < 0)
		return (NOP);
	if (!(st = rl_catline(fd, c, ln, &it)))
		while (!(st = sh_lex(fd, toks, &it, ln)))
			;
	return (st);
}
