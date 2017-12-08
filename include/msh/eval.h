/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/eval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:05:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EVAL_H
# define MSH_EVAL_H

# include "sh.h"
# include "exe.h"
# include "bi.h"
# include "lex.h"
# include "reduce.h"

typedef enum	e_shs
{
	SH_OK = OK,
	SH_NOK = NOK,
	SH_NEXT = NOK + 1,
	SH_BREAK = NOK + 2,
	SH_BREAK_NOK = NOK + 3
}				t_shs;

extern t_st		sh_eval_sep(t_sh *self, t_job **pjob, t_tok *tok);
extern t_st		sh_eval_bi(t_sh *self, t_job **pjob, t_tok *tok);
extern t_st		sh_eval_exe(t_sh *self, t_job **pjob, t_tok *tok);
extern t_st		sh_eval_pipe(t_sh *self, t_job **job, t_tok *tok);
extern t_st		sh_eval_rin(t_sh *self, t_job **job, t_tok *tok);
extern t_st		sh_eval_rout(t_sh *self, t_job **pjob, t_tok *tok);
extern t_st		sh_eval_heredoc(t_sh *self, t_job **pjob, t_tok *tok);

#endif
