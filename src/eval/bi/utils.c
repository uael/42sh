/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi/utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:11:14 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bi.h"

int				sh_bi_retf(t_sh *self, int code, char const *msg, ...)
{
	va_list	ap;

	if (!msg)
		return (code);
	va_start(ap, msg);
	if (code && !self->bi_merge_out)
		ft_omstream_vwritef(&self->bi_err, msg, ap);
	else
		ft_omstream_vwritef(&self->bi_out, msg, ap);
	va_end(ap);
	return (code);
}

int				sh_bi_zretf(t_sh *self, int code, char const *msg, ...)
{
	va_list	ap;

	if (!msg)
		return (code);
	va_start(ap, msg);
	if (code <= 0 && !self->bi_merge_out)
		ft_omstream_vwritef(&self->bi_err, msg, ap);
	else
		ft_omstream_vwritef(&self->bi_out, msg, ap);
	va_end(ap);
	return (code);
}

static int		sh_bi_flush(t_sh *sh, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	ft_omstream_flush(&sh->bi_err, STDERR_FILENO);
	ft_omstream_flush(&sh->bi_out, STDOUT_FILENO);
	return (sh->st);
}

inline void		sh_bi_job(t_job *job, char **av, char **env)
{
	ft_job_fn(job, (t_job_fn)sh_bi_flush, av, env);
}
