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

static inline int	ouput(int ac, char **av, char**envv)
{
	(void)ac;
	(void)envv;
	ft_putf(STDOUT_FILENO, av[0]);
	return (EXIT_SUCCESS);
}

inline int			sh_evalheredoc(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	size_t	i;
	t_tok	*op;
	t_proc	out;
	t_proc	*proc;

	(void)fd;
	(void)ln;
	op = sh_tokpeek(toks);
	tok = sh_toknext(toks);
	i = job->processes.len - 1;
	proc = ft_vecat((t_vec *)&job->processes, i);
	sh_procfn(&out, ouput, NULL);
	if (ft_isdigit(*op->val))
		proc->src[STDIN_FILENO] = *op->val - '0';
	out.argv = ft_malloc(2 * sizeof(char **));
	out.argv[0] = ft_strdup(tok->val);
	out.argv[1] = NULL;
	ft_veccput((t_vec *)&job->processes, i, &out);
	sh_toknext(toks);
	return (YEP);
}
