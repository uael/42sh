/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int			sh_evalcmp(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	redir;
	t_tok	*op;

	(void)fd;
	op = sh_tokpeek(toks);
	if ((tok = sh_toknext(toks))->id != TOK_WORD)
		return (sh_parseerr(*ln, tok, "Expected `<filename>' got `%s'",
			sh_tokstr(tok)));
	proc = ft_vecback((t_vec *)&job->processes);
	while (tok->id == TOK_WORD)
	{
		if (ft_isdigit(*op->val))
			redir.from = *op->val - '0';
		else
			redir.from = STDIN_FILENO;
		if ((redir.to = open(tok->val, O_RDWR | O_CREAT, 0644)) < 0)
			return (sh_parseerr(*ln, tok, "%s: %e", tok->val, errno));
		ft_veccpush((t_vec *)&proc->redirs, &redir);
		tok = sh_toknext(toks);
	}
	return (YEP);
}
