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

# define SH_EXIT(c, sh, ...) (ft_fatal(c, (t_dtor)sh_dtor, sh, __VA_ARGS__))

typedef struct	s_sh
{
	t_lexer		lexer;
	t_vstr		env;
	int			st;
}				t_sh;

extern t_st		sh_init_stream(t_sh *self, char **env, t_istream *stream);
extern t_st		sh_init_file(t_sh *self, char **env, char const *filename);
extern void		sh_dtor(t_sh *self);
extern t_st		sh_prompt(t_sh *self, char *prompt);
extern t_st		msh(t_sh *self);

#endif
