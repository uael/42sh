/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/lex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_LEX_H
# define MSH_LEX_H

# include "sh.h"
# include "toks.h"

extern t_ret	msh_lex(t_lexer *self);
extern t_tok	*msh_peek(t_msh *self);
extern t_tok	*msh_peekn(t_msh *self, size_t n);
extern t_tok	*msh_next(t_msh *self, t_tok **next);
extern t_tok	*msh_consume(t_msh *self, uint8_t id);

#endif
