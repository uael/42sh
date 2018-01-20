/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc/kind.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_KIND_H
# define USH_PROC_KIND_H

# include "sh.h"
# include "cmderr.h"

typedef enum	e_prockd
{
	PROC_EXE,
	PROC_FN,
	PROC_SH,
	PROC_CMDERR
}				t_prockd;

typedef int		(t_procfn)(int ac, char **av, char **envv);

typedef union	u_procu
{
	char		*exe;
	t_procfn	*fn;
	t_subsh		sh;
	t_cmderr	cmderr;
}				t_procu;

#endif
