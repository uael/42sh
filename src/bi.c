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
	else if (!ft_strcmp(exe, "echo"))
		 return (sh_biecho);
	else if (!ft_strcmp(exe, "env"))
		 return (sh_bienv);
	else if (!ft_strcmp(exe, "exit"))
		 return (sh_biexit);
	else if (!ft_strcmp(exe, "setenv"))
		 return (sh_bisetenv);
	else if (!ft_strcmp(exe, "unsetenv"))
		 return (sh_biunsetenv);
	return (NULL);
}
