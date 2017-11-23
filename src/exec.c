/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 18:11:04 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wait.h>

#include "msh.h"

static void		msh_sigint_hdl(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_puts(1, "\n");
	signal(SIGINT, msh_sigint_hdl);
}

static t_ret	msh_cmd(t_msh *self, char *exe, char **av)
{
	pid_t	pid;

	signal(SIGINT, msh_sigint_hdl);
	if ((pid = fork()) == 0)
		execve(exe, av, self->env.buf);
	else if (pid < 0)
		return (RET_ERR);
	wait(&pid);
	return (RET_OK);
}

static t_ret	msh_cmd_nf(t_msh *self, t_ret ret, char *exe)
{
	t_tok *tok;

	while ((tok = msh_next(self, NULL)) && tok->id)
		if (tok->id == '\n')
			break ;
	if (ret == RET_ERR)
		return (ret);
	(void)self;
	ft_puts(2, "msh: command not found: '");
	ft_puts(2, exe);
	ft_putl(2, "'.");
	return (RET_NOK);
}

static t_shrule	msh_bi(t_tok *tok)
{
	t_dstr	*ident;

	ident = ft_tok_ident(tok);
	if (strcmp("echo", ident->buf) == 0)
		return (msh_bi_echo);
	if (strcmp("cd", ident->buf) == 0)
		return (msh_bi_cd);
	if (strcmp("setenv", ident->buf) == 0)
		return (msh_bi_setenv);
	if (strcmp("unsetenv", ident->buf) == 0)
		return (msh_bi_unsetenv);
	if (strcmp("unsetenv", ident->buf) == 0)
		return (msh_bi_env);
	if (strcmp("unsetenv", ident->buf) == 0)
		return (msh_bi_exit);
	return (NULL);
}

inline t_ret	msh_exec(t_msh *self, t_tok *tok)
{
	t_vstr		av;
	t_ret		ret;
	t_dstr		*ident;
	char		exe[4096];
	t_shrule	rule;

	if ((rule = msh_bi(tok)))
		return ((*rule)(self, tok));
	ident = ft_tok_ident(tok);
	if ((ret = msh_path_lookup(self, ft_dstr_begin(ident),
		S_IFREG | S_IXUSR, exe)) != RET_OK)
		return (msh_cmd_nf(self, ret, ft_dstr_begin(ident)));
	if (msh_av(self, &av, exe) == RET_ERR)
		return (RET_ERR);
	ret = msh_cmd(self, exe, av.buf);
	ft_vstr_dtor(&av, NULL);
	return (ret);
}
