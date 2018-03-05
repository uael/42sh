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

typedef struct	s_for
{
	char const	*name;
	t_vec		words;
	t_deq		body;
	char		*ln;
}				t_for;

typedef struct	s_ctx
{
	t_deq		*toks;
	size_t		stop;
	char const	*ln;
	t_job		*root;
	t_job		*job;
	t_proc		*proc;
	t_map		vars;
}				t_ctx;

typedef void	(t_evalcb)(t_ctx *ctx, t_tok *tok);

extern t_evalcb	*g_eval[];

extern void		sh_eval(t_deq *toks, char const *ln);
extern void		sh_evalexport(t_map *vars);
extern void		sh_evalif(t_ctx *ctx, t_tok *tok);
extern void		sh_evalwhile(t_ctx *ctx, t_tok *tok);
extern void		sh_evalfor(t_ctx *ctx, t_tok *tok);
extern void		sh_evalfuncdef(t_ctx *ctx, t_tok *tok);
extern void		sh_evalampr(t_ctx *ctx, t_tok *tok);
extern void		sh_evalcmp(t_ctx *ctx, t_tok *tok);
extern void		sh_evalheredoc(t_ctx *ctx, t_tok *tok);
extern void		sh_evalherenow(t_ctx *ctx, t_tok *tok);
extern void		sh_evallamp(t_ctx *ctx, t_tok *tok);
extern void		sh_evalramp(t_ctx *ctx, t_tok *tok);
extern void		sh_evalraout(t_ctx *ctx, t_tok *tok);
extern void		sh_evalword(t_ctx *ctx, t_tok *tok);
extern void		sh_evaltest(t_ctx *ctx, t_tok *tok);
extern void		sh_evalassign(t_ctx *ctx, t_tok *tok);
extern void		sh_evaland(t_ctx *ctx, t_tok *tok);
extern void		sh_evalor(t_ctx *ctx, t_tok *tok);
extern void		sh_evalbang(t_ctx *ctx, t_tok *tok);
extern void		sh_evalsubshell(t_ctx *ctx, t_tok *tok);
extern void		sh_evalbracegrp(t_ctx *ctx, t_tok *tok);
extern void		sh_evalrin(t_ctx *ctx, t_tok *tok);
extern void		sh_evalrout(t_ctx *ctx, t_tok *tok);
extern void		sh_evalpipe(t_ctx *ctx, t_tok *tok);
extern void		sh_evalpipeand(t_ctx *ctx, t_tok *tok);
extern int		sh_evalfn(t_proc *proc);

#endif
