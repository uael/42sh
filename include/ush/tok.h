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

# include <libft.h>
# include <librl.h>

# include "err.h"
# include "var.h"

# define ISREOL(IT) (*(IT) == '\n')
# define ISWEOL(IT) (*(IT) == '\r' && *((IT) + 1) == '\n')
# define ISEOL(IT) (ISREOL(IT) || ISWEOL(IT))

enum			e_tok
{
	TOK_END = '\0',
	TOK_HEREDOC = TOK_END + 1,
	TOK_RAOUT,
	TOK_LAMP,
	TOK_RAMP,
	TOK_CMP,
	TOK_EOL = '\n',
	TOK_RPOUT = TOK_EOL + 1,
	TOK_AMPR,
	TOK_LAND,
	TOK_LOR,
	TOK_WORD,
	TOK_NOT = '!',
	TOK_AMP = '&',
	TOK_LPAR = '(',
	TOK_RPAR = ')',
	TOK_SEMICOLON = ';',
	TOK_RIN = '<',
	TOK_ROUT = '>',
	TOK_PIPE = '|'
};

typedef struct	s_tok
{
	uint16_t	len;
	uint16_t	pos;
	uint8_t		id;
	uint8_t		padding[3];
}				t_tok;

extern char		*sh_tokstr(t_tok *tok);
extern t_tok	*sh_tokpeek(t_deq *toks);
extern t_tok	*sh_toknext(t_deq *toks);
extern t_tok	*sh_tokpos(t_tok *tok, char const *it, char const *ln);
extern void		sh_tokdtor(t_tok *tok);

#endif
