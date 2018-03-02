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

# include <libps.h>

# include "shell.h"
# include "tok.h"

struct s_if;

typedef struct	s_subshell
{
	t_deq		toks;
	char		*ln;
}				t_subshell;

typedef enum	e_elsek
{
	ELSE_NONE = 0,
	ELSE_ELSE,
	ELSE_ELIF
}				t_elsek;

typedef union	u_else
{
	t_deq		body;
	struct s_if	*elif;
}				t_else;

typedef struct	s_if
{
	t_deq		body;
	t_deq		cond;
	char		*ln;
	t_elsek		elsekind;
	t_else		elsepart;
}				t_if;

typedef struct	s_while
{
	t_deq		body;
	t_deq		cond;
	char		*ln;
}				t_while;

typedef struct	s_ctx
{
	t_deq		*toks;
	size_t		stop;
	char const	*ln;
	t_job		*job;
	t_proc		*proc;
	t_map		vars;
}				t_ctx;

extern int		sh_eval(int fd, t_deq *toks, char **ln);
extern int		sh_evallist(int fd, t_deq *toks, char **ln);
extern int		sh_evalandor(t_job *j, int fd, t_deq *ts, char **ln);
extern int		sh_evalpipeline(t_job *job, int fd, t_deq *toks, char **ln);

extern int		sh_evalcmd(t_proc *proc, int fd, t_deq *toks, char **ln);
extern int		sh_evalsimple(t_proc *proc, int fd, t_deq *toks, char **ln);
extern int		sh_evalcompound(t_proc *proc, int fd, t_deq *toks, char **ln);
extern int		sh_evalsubshell(t_proc *proc, int fd, t_deq *toks, char **ln);
extern int		sh_evalbracegrp(t_proc *proc, int fd, t_deq *toks, char **ln);
extern int		sh_evalifclause(t_proc *prc, int fd, t_deq *toks, char **ln);
extern int		sh_evalwhileclause(t_proc *prc, t_deq *toks, char **ln);
extern int		sh_evalfn(t_proc *proc);
extern int		sh_evalfuncdef(t_proc *proc, int fd, t_deq *toks, char **ln);
extern int		sh_evalargv(t_proc *proc, t_map *v, t_deq *toks, char **ln);
extern int		sh_evalredir(t_proc *proc, t_deq *toks, char **ln);
extern char		*sh_redirword(t_proc *proc, char *dst, t_deq *toks, char *ln);
extern int		sh_evalrin(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evalrout(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evalcmp(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evalraout(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evalheredoc(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evallamp(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evalramp(t_proc *proc, t_deq *toks, char **ln);
extern int		sh_evalampr(t_proc *proc, t_deq *toks, char **ln);

extern int		sh_evalassign(t_tok *tok, t_deq *toks, t_map *map, char *ln);
extern int		sh_evalnewlines(t_deq *toks);
extern int		sh_evallinebreak(t_deq *toks);
extern int		sh_evalsepop(t_deq *toks);
extern int		sh_evalsep(t_deq *toks);
extern int		sh_evalsepseq(t_deq *toks);

#endif
