/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 15:19:55 by null             ###   ########.fr       */
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

static t_ret	msh_cmd(t_msh *self, char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, msh_sigint_hdl);
	if (pid == 0)
		execve(path, args, self->env.buf);
	else if (pid < 0)
	{
		ft_putl(1, "Execution failed.");
		return (RET_ERR);
	}
	wait(&pid);
	return (RET_OK);
}

static t_ret	msh_cmd_nf(t_msh *self, t_ret ret, char *cmd)
{
	t_tok *tok;

	while ((tok = msh_next(self, NULL)) && tok->id)
		if (tok->id == '\n')
			break ;
	if (ret == RET_ERR)
		return (ret);
	(void)self;
	ft_puts(2, "msh: command not found: '");
	ft_puts(2, cmd);
	ft_putl(2, "'.");
	return (RET_NOK);
}

inline t_ret	msh_exec(t_msh *self, t_tok *tok)
{
	t_tok	*end;
	t_vstr	av;
	t_ret	ret;
	char	*ex;

	if ((ret = msh_path_lookup(self, ft_dstr_begin(&tok->val->val.ident),
		S_IFREG | S_IXUSR, &ex)) != RET_OK)
		return (msh_cmd_nf(self, ret, ft_dstr_begin(&tok->val->val.ident)));
	ft_vstr_ctor(&av);
	if (!ft_vstr_pushc(&av, ex))
		return (RET_ERR);
	while ((end = msh_next(self, NULL)) && end->id)
		if (end->id == MSH_TOK_WORD)
		{
			if (!ft_vstr_pushc(&av, end->val->val.ident.buf))
				return (RET_ERR);
		}
		else if (!ft_strchr(" \t", end->id))
			break ;
	if (!ft_vstr_pushc(&av, NULL))
		return (RET_ERR);
	ret = msh_cmd(self, ex, av.buf);
	free(ex);
	ft_vstr_dtor(&av, NULL);
	return (ret);
}
