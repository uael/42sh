/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_H
# define API_H

# include "libps.h"

static t_map		g_binaries_stack = {
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
static t_map		g_builtins_stack = {
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(t_procbi *), NULL, NULL
};

extern t_map		*g_binaries;
extern t_map		*g_builtins;
extern t_errcb		*g_errcb;
extern t_fatalcb	*g_fatalcb;
extern t_bool		g_tty;
extern pid_t		g_pgid;
extern pid_t		g_pid;
extern TTY			g_tcmode;

#endif
