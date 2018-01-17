/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse/pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/parse.h"

#define CMD "Unexpected token `%s'"

inline t_job	*sh_parsepipeline(int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_job	*job;

	ft_vecgrow((t_vec *)g_pool, 1);
	job = ft_vecend((t_vec *)g_pool); //todo: ctor
	ft_vecctor((t_vec *)&job->pipeline, sizeof(t_proc));
	if (!sh_parsecommand(job, fd, toks, ln))
		return (NULL);
	while (1)
		if (sh_tokpeek(toks)->id == TOK_PIPE)
		{
			while ((tok = sh_toknext(toks)))
				if (tok->id != TOK_EOL)
					break ;
			job->and = 1;
			if (!sh_parsecommand(job, fd, toks, ln))
				return (sh_parseerr(*ln, tok, CMD, sh_tokidstr(TOK_PIPE)));
		}
		else
			return (ft_vecpush((t_vec *)g_pool));
}
