/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 15:43:46 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/bi.h"

inline t_bi_fn	sh_bi(char *exe)
{
	if (ft_strcmp("cd", exe) == 0)
		return (sh_bi_cd);
	if (ft_strcmp("echo", exe) == 0)
		return (sh_bi_echo);
	if (ft_strcmp("env", exe) == 0)
		return (sh_bi_env);
	if (ft_strcmp("exit", exe) == 0)
		return (sh_bi_exit);
	if (ft_strcmp("setenv", exe) == 0 || ft_strcmp("export", exe) == 0)
		return (sh_bi_setenv);
	if (ft_strcmp("unsetenv", exe) == 0 || ft_strcmp("unset", exe) == 0)
		return (sh_bi_unsetenv);
	return (NULL);
}

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
