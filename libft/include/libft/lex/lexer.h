/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 11:21:55 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_LEXER_H
# define LIBFT_LEX_LEXER_H

# include "tok.h"

typedef struct	s_lexer
{
	t_deq		srcs;
	t_deq		toks;
	t_vec		vals;
	t_vec		rules;
	t_src		*src;
}				t_lexer;

typedef int		(*t_lrule)(t_lexer *, t_tok *, char);

extern void		ft_lexer_dtor(t_lexer *self);
extern void		ft_lexer_init_stream(t_lexer *self, t_istream *stream);
extern int		ft_lexer_init_file(t_lexer *self, char const *filename);
extern void		ft_lexer_init_str(t_lexer *self, char const *s);
extern void		ft_lexer_ctor(t_lexer *self);
extern size_t	ft_lexer_clean(t_lexer *self);
extern ssize_t	ft_lexer_scan(t_lexer *self, size_t n);
extern ssize_t	ft_lexer_until(t_lexer *self, uint8_t id);
extern ssize_t	ft_lexer_next(t_lexer *self, char *peek, size_t n);
extern int		ft_lexer_getc(t_lexer *self, char *peek, char *next);
extern int		ft_lexer_peek(t_lexer *self, char *peek, size_t n);
extern t_src	*ft_lexer_src(t_lexer *self);
extern void		ft_lexer_unshift(t_lexer *self, t_src *src);

extern int		ft_tok_peek(t_lexer *self, size_t n, t_tok **peek);
extern ssize_t	ft_tok_next(t_lexer *self, size_t n, t_tok **peek);
extern size_t	ft_tok_skip(t_lexer *self, size_t n, t_tok **prevs);

#endif
