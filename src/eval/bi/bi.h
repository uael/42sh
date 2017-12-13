/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi/bi.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:11:14 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_BI_BI_H
# define EVAL_BI_BI_H

# include "msh/eval.h"

typedef int		(*t_bi_fn)(t_sh *sh, int ac, char **av, t_job *out);

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
