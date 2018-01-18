/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/eval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_EVAL_H
# define USH_EVAL_H

# include "shell.h"
# include "pool.h"
# include "tok.h"

extern int		sh_parse(int fd, t_deq *toks, char **ln);
extern int		sh_evallist(int fd, t_deq *toks, char **ln);
extern int		sh_evalandor(t_job *job, int fd, t_deq *toks, char **ln);
extern int		sh_evalpipeline(t_job *job, int fd, t_deq *toks, char **ln);
extern int		sh_evalcommand(t_job *job, int fd, t_deq *toks, char **ln);

#endif
