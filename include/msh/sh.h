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
# include <librl.h>

# define N_SH COLOR_RED COLOR_BOLD "21sh: " COLOR_RESET

typedef enum	e_sh_m
{
	SH_TTY,
	SH_NOTTY,
	SH_AV,
	SH_C
}				t_sh_m;

typedef struct	s_sh_tok
{
	uint8_t		id;
	char		*val;
	size_t		len;
}				t_sh_tok;

typedef struct	s_sh
{
	t_sh_m		mode;
	t_sh_tok	*toks;
	size_t		toks_len;
	size_t		toks_cur;
	t_vstr		env;
	t_vstr		history;
	size_t		cursor;
	char		*ln;
	t_worker	worker;
	t_omstream	bi_out;
	t_omstream	bi_err;
	t_bool		bi_merge_out;
	int			st;
	t_rl		rl;

	t_lexer		lexer;
}				t_sh;

extern int		sh_init(t_sh *self, char **env);
extern int		sh_init_file(t_sh *self, char **env, char const *filename);
extern void		sh_dtor(t_sh *self);
extern void		sh_prompt(t_sh *self, char *prompt);
extern void		sh_clean(t_sh *self);
extern int		sh_eval(t_sh *self, char *ln);

#endif
