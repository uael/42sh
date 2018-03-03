/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/func.h"

static uint8_t		g_end[] = {
	['('] = ')',
	['{'] = '}',
	[TOK_IF] = TOK_FI,
	[TOK_WHILE] = TOK_DONE,
};

static inline int	avcount(char *av[])
{
	int c;

	c = 0;
	while (*av++)
		++c;
	return (c);
}

inline int			sh_evalfn(t_proc *proc)
{
	t_func	*fn;
	char	*av0;
	char	*fname;

	av0 = g_sh->av[0];
	g_sh->av = proc->argv;
	g_sh->ac = avcount(proc->argv);
	g_sh->tty = 0;
	fname = g_sh->av[0];
	if (!(fn = sh_funcget(fname)))
		return (EXIT_FAILURE);
	g_sh->av[0] = av0;
	sh_eval(-1, &fn->body, (char **)&fn->ln) ? (g_sh->status = 1) : 0;
	g_sh->av[0] = fname;
	return (g_sh->status);
}

inline int			sh_evalfuncdef(t_proc *proc, int fd, t_deq *toks, char **ln)
{
	t_tok		*beg;
	t_tok		*tok;
	t_tok		*name;
	t_deq		body;
	char const	*id;

	(void)proc;
	fd = 1;
	name = sh_toknext(toks);
	beg = sh_toknext(toks);
	ft_deqctor(&body, sizeof(t_tok));
	while ((tok = sh_toknext(toks)))
	{
		if (tok->id == beg->id)
			++fd;
		else if (tok->id == g_end[beg->id] && !--fd)
			break ;
		*(t_tok *)ft_deqpush(&body) = *tok;
	}
	sh_toknext(toks);
	id = ft_strndup(*ln + name->pos, name->len);
	sh_funcset(id, &body, *ln);
	free((void *)id);
	return (YEP);
}
