/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 15:10:56 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

#include "msh.h"

inline t_st	msh_init_stream(t_msh *self, char **env, t_istream *stream)
{
	t_st st;

	FT_INIT(self, t_msh);
	ft_vstr_ctor(&self->env);
	ft_dstr_ctor(&self->out);
	ft_dstr_ctor(&self->err);
	if (ST_NOK(st = msh_initenv(self, env)))
		return (st);
	if (ST_NOK(st = ft_lexer_init_stream(&self->lexer, stream)))
		return (st);
	return (msh_lex(&self->lexer));
}

inline t_st	msh_init_file(t_msh *self, char **env, char const *filename)
{
	t_st st;

	FT_INIT(self, t_msh);
	ft_vstr_ctor(&self->env);
	ft_dstr_ctor(&self->out);
	ft_dstr_ctor(&self->err);
	if (ST_NOK(st = msh_initenv(self, env)))
		return (st);
	if (ST_NOK(st = ft_lexer_init_file(&self->lexer, filename)))
		return (st);
	return (msh_lex(&self->lexer));
}

inline void	msh_dtor(t_msh *self)
{
	ft_dstr_dtor(&self->out, NULL);
	ft_dstr_dtor(&self->err, NULL);
	ft_vstr_dtor(&self->env, (void (*)(char **))ft_pfree);
	ft_lexer_dtor(&self->lexer);
}

inline t_st	msh_prompt(t_msh *self, char *prompt)
{
	size_t	l;
	char	cwd[4096 + 1];
	char	*p;
	char	**home;
	t_st	st;

	if (!(p = getcwd(cwd, 4096)))
		return (ENO);
	if (ISE(st = msh_envadd(self, "PWD", p)))
		return (st);
	if ((home = msh_getenv(self, "HOME")) && ft_strbegw(*home + 5, p))
	{
		if (p[l = ft_strlen(*home + 5)] != '\0')
			ft_memmove(p + 1, p + l, (ft_strlen(p) - l + 1) * sizeof(char));
		else
			p[1] = '\0';
		*p = '~';
	}
	ft_puts(0, p);
	ft_puts(0, prompt);
	return (OK);
}

inline t_st	msh(t_msh *self)
{
	t_tok	*tok;
	t_st	st;

	while (1)
		if (!(tok = msh_next(self, NULL)))
			return (NOK);
		else if (tok->id == '\n')
			return (OK);
		else if (ft_strchr(";\t ", tok->id))
			continue ;
		else if (ISE(st = msh_eval(self, tok)))
			return (st);
		else
			ft_lexer_clean(&self->lexer);
}
