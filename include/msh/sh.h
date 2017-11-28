/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/sh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SH_H
# define MSH_SH_H

# include <libft.h>

# define MSH_EXIT(code, msh) (exit(ft_dtor((code),(t_dtor)msh_dtor, msh, NULL)))

typedef struct	s_msh
{
	t_lexer		lexer;
	t_dstr		out;
	t_dstr		err;
	t_vstr		env;
	int			st;
}				t_msh;

extern t_st		msh_init_stream(t_msh *self, char **env, t_istream *stream);
extern t_st		msh_init_file(t_msh *self, char **env, char const *filename);
extern void		msh_dtor(t_msh *self);
extern t_st		msh_prompt(t_msh *self, char *prompt);
extern t_st		msh(t_msh *self);

#endif
