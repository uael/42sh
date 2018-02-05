/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"
#include "ush/shell.h"

inline int			sh_lexbslash(int fd, char **it, char **ln)
{
	int st;

	if (**it == '\\' && ((ISREOL(*it + 1) && !*(*it + 2)) ||
		((ISWEOL(*it + 1) && !*(*it + 3)))))
	{
		*it += ISREOL(*it + 1) ? 2 : 3;
		if (fd >= 0 && (st = rl_catline(fd, -2, ln, it)))
			return (st);
	}
	return (YEP);
}
