/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline void	sh_init_stream(t_sh *self, t_sh_m m, char **env, t_istream *stream)
{
	FT_INIT(self, t_sh);
	self->mode = m;
	sh_initenv(&self->env, env);
	if (self->mode == SH_TTY)
	{
		ft_src_init_stream(&self->tty, stream);
		ft_lexer_ctor(&self->lexer);
	}
	else
		ft_lexer_init_stream(&self->lexer, stream);
	ft_worker_ctor(&self->worker);
	sh_lex(&self->lexer);
}

inline int	sh_init_file(t_sh *self, t_sh_m m, char **env, char const *filename)
{
	FT_INIT(self, t_sh);
	self->mode = m;
	sh_initenv(&self->env, env);
	if (self->mode == SH_TTY)
	{
		if (ft_src_init_file(&self->tty, filename))
			return (WUT);
		ft_lexer_ctor(&self->lexer);
	}
	else if (ft_lexer_init_file(&self->lexer, filename))
		return (WUT);
	ft_worker_ctor(&self->worker);
	sh_lex(&self->lexer);
	return (YEP);
}

inline void	sh_dtor(t_sh *self)
{
	ft_omstream_close(&self->bi_err);
	ft_omstream_close(&self->bi_out);
	ft_vstr_dtor(&self->env, (t_dtor)ft_pfree);
	ft_vstr_dtor(&self->history, (t_dtor)ft_pfree);
	ft_lexer_dtor(&self->lexer);
	ft_worker_dtor(&self->worker);
	if (self->mode == SH_TTY)
		ft_src_dtor(&self->tty);
}

inline void	sh_prompt(t_sh *self, char *prompt)
{
	size_t	l;
	char	cwd[PATH_MAX + 1];
	char	*p;
	char	*home;

	if (!(p = getcwd(cwd, PATH_MAX)))
	{
		THROW(WUT);
		ft_puts(0, prompt);
		return ;
	}
	sh_envadd(&self->env, "PWD", p);
	if ((home = ft_getenv(self->env.buf, "HOME")) && ft_strbegw(home, p))
	{
		if (p[l = ft_strlen(home)] != '\0')
			ft_memmove(p + 1, p + l, (ft_strlen(p) - l + 1) * sizeof(char));
		else
			p[1] = '\0';
		*p = '~';
	}
	ft_puts(0, p);
	ft_puts(0, prompt);
}

extern void	sh_clean(t_sh *self)
{
	ft_omstream_clear(&self->bi_out);
	ft_omstream_clear(&self->bi_err);
	ft_worker_clear(&self->worker);
	ft_lexer_clean(&self->lexer);
}
