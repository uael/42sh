/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

inline int			sh_evalheredoc(t_proc *proc, t_deq *toks, char **ln)
{
	t_tok	*tok;

	tok = sh_toknext(toks);
	if (proc->in)
		free(proc->in);
	proc->in = ft_strndup(*ln + tok->pos, tok->len);
	sh_toknext(toks);
	return (YEP);
}
