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

extern t_st		sh_lex(t_lexer *self);
extern t_tok	*sh_peek(t_sh *self);
extern t_tok	*sh_next(t_sh *self, t_tok **next);
extern void		sh_consume_line(t_sh *self);
extern t_tok	*sh_skip(t_sh *self, char *ids);

#endif
