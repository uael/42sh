/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/lex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_LEX_H
# define USH_LEX_H

# include "tok.h"

typedef struct	s_src
{
	int			fd;
	char		**it;
	char		**ln;
}				t_src;

typedef int		(t_lexcb)(int fd, t_deq *toks, char **ln);

extern size_t	sh_synbracket(t_src *s, t_deq *a, t_tok *o, size_t i);
extern int		sh_syn(t_src *s, t_tok **a, t_tok *b);

extern int		sh_lex(int fd, char **it, char **ln, t_lexcb *cb);
extern int		sh_lexline(t_src *src, t_deq *toks, t_bool new);
extern int		sh_tokenize(t_src *s, t_tok *tok);
extern int		sh_lexreduce(t_src *s, t_deq *toks, size_t from);
extern int		sh_lexcheck(t_src *s, t_deq *toks);
extern int		sh_lexdollar(t_src *s, t_tok *tok);
extern int		sh_lexop(t_src *s, t_tok *tok);
extern int		sh_lexbslash(t_src *src);
extern int		sh_lexword(t_src *s, t_tok *tok);
extern int		sh_lexheredoc(t_src *s, t_tok *tok);
extern t_bool	sh_isname(char *word);
extern t_bool	sh_isident(char const *word, size_t n);

#endif
