/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UNEXPTD "Unexpected redirection `%s' for empty command line"

inline int		sh_evalredir(t_proc *proc, t_deq *toks, char **ln)
{
	t_tok	*tok;

	tok = sh_tokpeek(toks);
	if (tok->id == '<')
		return (sh_evalrin(proc, toks, ln));
	if (tok->id == '>' || tok->id == TOK_RPOUT)
		return (sh_evalrout(proc, toks, ln));
	if (tok->id == TOK_CMP)
		return (sh_evalcmp(proc, toks, ln));
	if (tok->id == TOK_RAOUT)
		return (sh_evalraout(proc, toks, ln));
	if (tok->id == TOK_AMPR)
		return (sh_evalampr(proc, toks, ln));
	if (tok->id == TOK_HEREDOC)
		return (sh_evalheredoc(proc, toks, ln));
	if (tok->id == TOK_LAMP)
		return (sh_evallamp(proc, toks, ln));
	if (tok->id == TOK_RAMP)
		return (sh_evalramp(proc, toks, ln));
	return (sh_evalerr(*ln, tok, UNEXPTD, sh_tokstr(tok)));
}
