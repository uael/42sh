/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/bi.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BI_H
# define MSH_BI_H

# include "exe.h"

extern t_cmd	msh_bi(char *exe);
extern t_st		msh_bi_echo(t_msh *self, t_vstr *av);
extern t_st		msh_bi_cd(t_msh *self, t_vstr *av);
extern t_st		msh_bi_setenv(t_msh *self, t_vstr *av);
extern t_st		msh_bi_unsetenv(t_msh *self, t_vstr *av);
extern t_st		msh_bi_env(t_msh *self, t_vstr *av);
extern t_st		msh_bi_exit(t_msh *self, t_vstr *av);

#endif
