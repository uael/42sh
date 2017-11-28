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
#include <limits.h>

#include "msh.h"

inline t_st	sh_init_stream(t_sh *self, char **env, t_istream *stream)
{
	t_st st;

	FT_INIT(self, t_sh);
	ft_vstr_ctor(&self->env);
	if (ST_NOK(st = sh_initenv(self, env)))
		return (st);
	if (ST_NOK(st = ft_lexer_init_stream(&self->lexer, stream)))
		return (st);
	return (sh_lex(&self->lexer));
}

inline t_st	sh_init_file(t_sh *self, char **env, char const *filename)
{
	t_st st;

	FT_INIT(self, t_sh);
	ft_vstr_ctor(&self->env);
	if (ST_NOK(st = sh_initenv(self, env)))
		return (st);
	if (ST_NOK(st = ft_lexer_init_file(&self->lexer, filename)))
		return (st);
	return (sh_lex(&self->lexer));
}

inline void	sh_dtor(t_sh *self)
{
	ft_vstr_dtor(&self->env, (void (*)(char **))ft_pfree);
	ft_lexer_dtor(&self->lexer);
}

inline t_st	sh_prompt(t_sh *self, char *prompt)
{
	size_t	l;
	char	cwd[PATH_MAX + 1];
	char	*p;
	char	**home;
	t_st	st;

	if (!(p = getcwd(cwd, PATH_MAX)))
		return (ENO);
	if (ISE(st = sh_envadd(self, "PWD", p)))
		return (st);
	if ((home = sh_getenv(self, "HOME")) && ft_strbegw(*home + 5, p))
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

inline t_st	msh(t_sh *self)
{
	t_tok	*tok;
	t_st	st;

	while (1)
		if (!(tok = sh_next(self, NULL)))
			return (NOK);
		else if (tok->id == '\n')
			return (OK);
		else if (ft_strchr(";\t ", tok->id))
			continue ;
		else if (ISE(st = sh_eval(self, tok)))
			return (st);
		else
			ft_lexer_clean(&self->lexer);
}
