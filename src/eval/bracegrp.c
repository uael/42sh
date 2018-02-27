/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bracegrp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static inline int	bracegrp(t_subshell *s)
{
	int		st;

	g_sh->tty = 0;
	sh_eval(-1, &s->toks, &s->ln) ? (g_sh->status = 1) : 0;
	st = g_sh->status;
	return (st);
}

static inline void	bracegrpdtor(t_subshell *s)
{
	ft_deqdtor(&s->toks, NULL);
	free(s->ln);
	free(s);
}

inline int			sh_evalbracegrp(t_proc *prc, int fd, t_deq *toks, char **ln)
{
	int			stack;
	t_subshell	*sh;
	t_tok		*tok;

	(void)fd;
	ft_deqctor(&(sh = ft_malloc(sizeof(t_subshell)))->toks, sizeof(t_tok));
	ps_procfn(prc, (t_proccb *)bracegrp, (t_dtor)bracegrpdtor, sh);
	stack = 0;
	while ((tok = sh_toknext(toks))->id != '}' || stack)
	{
		if (tok->id == '{')
			++stack;
		else if (tok->id == '}')
			--stack;
		*(t_tok *)ft_deqpush(&sh->toks) = *tok;
	}
	sh_toknext(toks);
	(*(t_tok *)ft_deqpush(&sh->toks)).id = TOK_END;
	sh->ln = ft_strdup(*ln);
	return (YEP);
}
