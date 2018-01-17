/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var/ifs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/var.h"

inline char		*sh_varifs(void)
{
	static char	*ifs = NULL;
	char		*eol;

	if (ifs)
		return (ifs);
	if (!(ifs = sh_getenv("IFS")))
		ifs = SH_IFS;
	else if ((eol = ft_strchr(ifs, '\n')))
		*eol = ' ';
	return (ifs);
}
