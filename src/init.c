/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 14:39:45 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "msh.h"

inline t_ret	msh_init_stream(t_msh *self, char **env, t_istream *stream)
{
	t_ret	r;

	FT_INIT(self, t_msh);
	ft_vstr_ctor(&self->env);
	ft_dstr_ctor(&self->out);
	ft_dstr_ctor(&self->err);
	if ((r = msh_initenv(self, env)) != RET_OK)
		return (r);
	if ((r = ft_lexer_init_stream(&self->lexer, stream)) != RET_OK)
		return (r);
	return (msh_lex(&self->lexer));
}

inline t_ret	msh_init_file(t_msh *self, char **env, char const *filename)
{
	t_ret r;

	FT_INIT(self, t_msh);
	ft_vstr_ctor(&self->env);
	ft_dstr_ctor(&self->out);
	ft_dstr_ctor(&self->err);
	if ((r = msh_initenv(self, env)) != RET_OK)
		return (r);
	if ((r = ft_lexer_init_file(&self->lexer, filename)) != RET_OK)
		return (r);
	return (msh_lex(&self->lexer));
}

inline t_ret	msh_init_str(t_msh *self, char **env, char const *str)
{
	t_ret r;

	FT_INIT(self, t_msh);
	ft_vstr_ctor(&self->env);
	ft_dstr_ctor(&self->out);
	ft_dstr_ctor(&self->err);
	if ((r = msh_initenv(self, env)) != RET_OK)
		return (r);
	if ((r = ft_lexer_init_str(&self->lexer, str)) != RET_OK)
		return (r);
	return (msh_lex(&self->lexer));
}

inline t_ret	msh_init_nstr(t_msh *self, char **env, char const *s, size_t n)
{
	t_ret r;

	FT_INIT(self, t_msh);
	ft_vstr_ctor(&self->env);
	ft_dstr_ctor(&self->out);
	ft_dstr_ctor(&self->err);
	if ((r = msh_initenv(self, env)) != RET_OK)
		return (r);
	if ((r = ft_lexer_init_nstr(&self->lexer, s, n)) != RET_OK)
		return (r);
	return (msh_lex(&self->lexer));
}

inline void		msh_dtor(t_msh *self)
{
	ft_dstr_dtor(&self->out, NULL);
	ft_dstr_dtor(&self->err, NULL);
	ft_vstr_dtor(&self->env, (void (*)(char **))ft_pfree);
	ft_lexer_dtor(&self->lexer);
}
