/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:54:42 by mc                #+#    #+#             */
/*   Updated: 2018/02/12 17:56:14 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** globctor, globdtor -
** find pathnames matching a pattern, free memory from globctor()
*/

#include "libft/glob.h"
#include "glob_climb_tree.h"

int		globctor(const char *pattern, int flags, t_glob *pglob)
{
/*
	handle_flags(GLOB_DOOFFS | GLOB_APPEND)

	if GLOB_ALTDIRFUNC:
		return GLOB_NOSYS

	files[] = glob_climb_tree(pattern, flags)

	if GLOB_NOCHECK and not files:
		return pattern
	if GLOB_NOMAGIC and not GLOB_MAGCHAR:
		return pattern

	pglob->gl_pathv = malloc(len(files))
	//TODO: flags: GLOB_MARK  (Append a slash to each name)

	if GLOB_NOSORT:
		for(i in range(len(file))):
			pglob->gl_pathv[i] = file[i]
	else:
		pglob->gl_pathv = sort(files)
*/
	(void)pattern; //TODO
	(void)flags; //TODO
	(void)pglob; //TODO

	return GLOB_SUCCESS;
}

void	globdtor(t_glob *pglob)
{
	char **av;

	av = pglob->gl_pathv + pglob->gl_offs;
	while (*av)
		free(av++);
	free(pglob->gl_pathv);
}
