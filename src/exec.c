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

#include "msh.h"

static void		msh_fork_sigint_hdl(int signo)
{
	(void)signo;
	ft_putc(1, '\n');
	ft_putc(0, '\n');
}

static t_ret	msh_cmd(t_msh *self, char *exe, char **av)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
		execve(exe, av, self->env.buf);
	else if (pid < 0)
		return (RET_ERR);
	signal(SIGINT, msh_fork_sigint_hdl);
	wait(&pid);
	signal(SIGINT, msh_sigint_hdl);
	return (RET_OK);
}

static t_ret	msh_cmd_nf(t_msh *self, t_ret ret, char *exe)
{
	t_tok *tok;

	while ((tok = msh_peek(self)) && tok->id)
	{
		if (tok->id == '\n')
			break ;
		msh_next(self, NULL);
	}
	if (ret == RET_ERR)
		return (ret);
	(void)self;
	ft_puts(2, "msh: command not found: '");
	ft_puts(2, exe);
	ft_putl(2, "'.");
	return (RET_NOK);
}

static t_shcmd	msh_bi(t_tok *tok)
{
	t_dstr	*ident;

	ident = ft_tok_ident(tok);
	if (ft_strcmp("cd", ident->buf) == 0)
		return (msh_bi_cd);
	if (ft_strcmp("echo", ident->buf) == 0)
		return (msh_bi_echo);
	if (ft_strcmp("env", ident->buf) == 0)
		return (msh_bi_env);
	if (ft_strcmp("exit", ident->buf) == 0)
		return (msh_bi_exit);
	if (ft_strcmp("setenv", ident->buf) == 0)
		return (msh_bi_setenv);
	if (ft_strcmp("unsetenv", ident->buf) == 0)
		return (msh_bi_unsetenv);
	if (ft_strcmp("unsetenv", ident->buf) == 0)
		return (msh_bi_env);
	return (NULL);
}

inline t_ret	msh_exec(t_msh *self, t_tok *tok)
{
	t_vstr		av;
	t_ret		ret;
	t_dstr		*ident;
	char		exe[4096];
	t_shcmd		rule;

	if ((rule = msh_bi(tok)))
	{
		if (msh_av(self, &av, exe) == RET_ERR)
			return (RET_ERR);
		ret = ((*rule)(self, &av));
		return (ft_dtor(ret, (t_dtor)ft_vstr_dtor, &av, NULL));
	}
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
