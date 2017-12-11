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

inline void	sh_init_stream(t_sh *self, char **env, t_istream *stream)
{
	FT_INIT(self, t_sh);
	ft_vstr_ctor(&self->env);
	ft_worker_ctor(&self->worker);
	ft_omstream_open(&self->bi_out);
	ft_omstream_open(&self->bi_err);
	sh_initenv(&self->env, env);
	ft_lexer_init_stream(&self->lexer, stream);
	sh_lex(&self->lexer);
}

inline t_st	sh_init_file(t_sh *self, char **env, char const *filename)
{
	t_st st;

	FT_INIT(self, t_sh);
	ft_vstr_ctor(&self->env);
	ft_worker_ctor(&self->worker);
	ft_omstream_open(&self->bi_out);
	ft_omstream_open(&self->bi_err);
	sh_initenv(&self->env, env);
	if (ST_NOK(st = ft_lexer_init_file(&self->lexer, filename)))
		return (st);
	sh_lex(&self->lexer);
	return (OK);
}

inline void	sh_dtor(t_sh *self)
{
	ft_omstream_close(&self->bi_err);
	ft_omstream_close(&self->bi_out);
	ft_vstr_dtor(&self->env, (t_dtor)ft_pfree);
	ft_lexer_dtor(&self->lexer);
	ft_worker_dtor(&self->worker);
}

inline t_st	sh_prompt(t_sh *self, char *prompt)
{
	size_t	l;
	char	cwd[PATH_MAX + 1];
	char	*p;
	char	*home;

	if (!(p = getcwd(cwd, PATH_MAX)) &&
		!(p = ft_getenv(self->env.buf, "PWD")))
		return (ft_ex_throw(NOK));
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
	return (OK);
}

extern void		sh_clean(t_sh *self)
{
	ft_omstream_clear(&self->bi_out);
	ft_omstream_clear(&self->bi_err);
	ft_worker_clear(&self->worker);
	ft_lexer_clean(&self->lexer);
}
