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

inline void	sh_biregister(void)
{
	ps_biregister("cd", sh_bicd);
	ps_biregister("echo", sh_biecho);
	ps_biregister("env", sh_bienv);
	ps_biregister("exit", sh_biexit);
	ps_biregister("export", sh_biexport);
	ps_biregister("setenv", sh_bisetenv);
	ps_biregister("unset", (t_procbi *)sh_biunset);
	ps_biregister("unsetenv", sh_biunsetenv);
	ps_biregister("history", sh_bihistory);
}
