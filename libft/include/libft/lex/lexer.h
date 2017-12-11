/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:46:37 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_LEXER_H
# define LIBFT_LEX_LEXER_H

# include "tok.h"

typedef t_st	(*t_lrule)(t_tok *, char, t_src *);

typedef struct	s_lexer
{
	t_deq		srcs;
	t_deq		toks;
	t_vec		vals;
	t_vec		rules;
}				t_lexer;

extern void		ft_lexer_dtor(t_lexer *self);
extern void		ft_lexer_init_stream(t_lexer *self, t_istream *stream);
extern t_st		ft_lexer_init_file(t_lexer *self, char const *filename);
extern void		ft_lexer_init_str(t_lexer *self, char const *s);
extern void		ft_lexer_init_nstr(t_lexer *self, char const *s, size_t n);
extern size_t	ft_lexer_clean(t_lexer *self);
extern t_sz		ft_lexer_scan(t_lexer *self, size_t n);
extern t_sz		ft_lexer_until(t_lexer *self, uint8_t id);
extern t_st		ft_lexer_getc(t_lexer *self, char *c);
extern t_st		ft_lexer_peek(t_lexer *self, size_t n, t_tok **peek);
extern t_sz		ft_lexer_next(t_lexer *self, size_t n, t_tok **peek);
extern size_t	ft_lexer_skip(t_lexer *self, size_t n, t_tok **prevs);
extern t_st		ft_lexer_match(t_tok *tok, t_src *src, size_t n, uint8_t id);

#endif
