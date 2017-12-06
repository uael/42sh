/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/bi.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 09:40:24 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BI_H
# define MSH_BI_H

# include "exe.h"

typedef int		(*t_bi_fn)(t_sh *sh, int ac, char **av, t_job *out);

extern t_bi_fn	sh_bi(char *exe);
extern int		sh_bi_retf(t_sh *self, int code, char const *msg, ...);
extern int		sh_bi_zretf(t_sh *self, int code, char const *msg, ...);
extern void		sh_bi_job(t_job *job, char **av, char **env);
extern int		sh_bi_echo(t_sh *sh, int ac, char **av, t_job *out);
extern int		sh_bi_cd(t_sh *sh, int ac, char **av, t_job *out);
extern int		sh_bi_setenv(t_sh *sh, int ac, char **av, t_job *out);
extern int		sh_bi_unsetenv(t_sh *sh, int ac, char **av, t_job *out);
extern int		sh_bi_env(t_sh *sh, int ac, char **av, t_job *out);
extern int		sh_bi_exit(t_sh *sh, int ac, char **av, t_job *out);

#endif
