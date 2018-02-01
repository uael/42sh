/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/bi.h"

inline t_procfn	*sh_bifn(char const *exe)
{
	if (!ft_strcmp(exe, "cd"))
		return (sh_bicd);
	if (!ft_strcmp(exe, "bg"))
		return (sh_bibg);
	if (!ft_strcmp(exe, "echo"))
		return (sh_biecho);
	if (!ft_strcmp(exe, "env"))
		return (sh_bienv);
	if (!ft_strcmp(exe, "exit"))
		return (sh_biexit);
	if (!ft_strcmp(exe, "export"))
		return (sh_biexport);
	if (!ft_strcmp(exe, "fg"))
		return (sh_bifg);
	if (!ft_strcmp(exe, "jobs"))
		return (sh_bijobs);
	if (!ft_strcmp(exe, "setenv"))
		return (sh_bisetenv);
	if (!ft_strcmp(exe, "unset"))
		return ((t_procfn *)sh_biunset);
	if (!ft_strcmp(exe, "unsetenv"))
		return (sh_biunsetenv);
	if (!ft_strcmp(exe, "history"))
		return (sh_bihistory);
	return (NULL);
}
