/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	subshell(t_subshell *s)
{
	int		st;

	g_sh->child = 1;
	sh_eval(-1, &s->toks, &s->ln) ? (g_sh->status = 1) : 0;
	st = g_sh->status;
	return (st);
}

static inline void	subshelldtor(t_subshell *s)
{
	ft_deqdtor(&s->toks, NULL);
	free(s->ln);
	free(s);
}

inline int			sh_evalsubshell(t_proc *prc, int fd, t_deq *toks, char **ln)
{
	int			depth;
	t_subshell	sh;
	t_tok		*tok;

	(void)fd;
	ft_bzero(&sh, sizeof(t_subshell));
	ft_deqctor(&sh.toks, sizeof(t_tok));
	depth = 0;
	while ((tok = sh_toknext(toks))->id != ')' || depth)
	{
		if (tok->id == '(')
			++depth;
		else if (tok->id == ')')
			--depth;
		*(t_tok *)ft_deqpush(&sh.toks) = *tok;
	}
	sh_toknext(toks);
	(*(t_tok *)ft_deqpush(&sh.toks)).id = TOK_END;
	sh.ln = *ln;
	if (g_sh->child)
	{
		subshell(&sh);
		ft_deqdtor(&sh.toks, NULL);
		return (YEP);
	}
	sh.ln = ft_strdup(sh.ln);
	ps_procfn(prc, (t_proccb *)subshell, (t_dtor)subshelldtor, ft_memdup(&sh,
		sizeof(t_subshell)));
	return (YEP);
}
