/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/sh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SH_H
# define MSH_SH_H

# include <libft.h>

# define SH_EXIT(c, sh, ...) (ft_fatal(c, (t_dtor)sh_dtor, sh, __VA_ARGS__))
# define N_SH COLOR_RED COLOR_BOLD "21sh: " COLOR_RESET

typedef struct	s_sh
{
	t_lexer		lexer;
	t_vstr		env;
	int			st;
	t_worker	worker;
	t_omstream	bi_out;
	t_omstream	bi_err;
	t_bool		bi_merge_out;
}				t_sh;

extern void		sh_init_stream(t_sh *self, char **env, t_istream *stream);
extern int		sh_init_file(t_sh *self, char **env, char const *filename);
extern void		sh_dtor(t_sh *self);
extern void		sh_prompt(t_sh *self, char *prompt);
extern void		sh_clean(t_sh *self);
extern int		sh_eval(t_sh *self);

#endif
