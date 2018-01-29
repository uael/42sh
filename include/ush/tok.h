/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/tok.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_TOK_H
# define USH_TOK_H

# include "lex.h"

extern t_tok	*sh_tokpeek(t_deq *toks);
extern t_tok	*sh_toknext(t_deq *toks);
extern t_tok	*sh_tokpos(t_tok *tok, char const *it, char const *ln);
extern void		sh_tokexplode(t_tok *tok, t_deq *into);

#endif
