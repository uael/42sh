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

typedef t_st	(*t_cmd)(t_sh *, t_vstr *);

extern t_st		sh_exe_av(t_sh *self, t_vstr *av, char *exe);
extern t_st		sh_exe_run(t_sh *self, t_vstr *av);
extern t_st		sh_exe_lookup(t_sh *self, char *file, int mode, char *exe);

#endif
