/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/exe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXE_H
# define MSH_EXE_H

# include "sh.h"

# define CMD_NOK(msg) ft_dtor(RET_NOK, NULL, NULL, (msg))

typedef t_ret	(*t_cmd)(t_msh *, t_vstr *);

extern t_ret	msh_exe_av(t_msh *self, t_vstr *av, char *exe);
extern t_ret	msh_exe_run(t_msh *self, t_vstr *av);
extern t_ret	msh_exe_lookup(t_msh *self, char *file, int mode, char *exe);

#endif
