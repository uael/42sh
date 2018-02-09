/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:54:42 by mc                #+#    #+#             */
/*   Updated: 2018/02/09 10:35:44 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** globctor, globdtor -
** find pathnames matching a pattern, free memory from globctor()
*/

#include "ush/glob.h"


int		globctor(const char *pattern, int flags, t_glob *pglob)
{
	(void)pattern; //TODO
	(void)flags; //TODO
	(void)pglob; //TODO
	return 42; //TODO
}

void	globdtor(t_glob *pglob)
{
	(void)pglob; //TODO
}
