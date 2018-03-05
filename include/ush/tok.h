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

# define TOKS_REDIR (1 << 0)
# define TOKS_WORD (1 << 1)
# define TOKS_END (1 << 2)
# define TOKS_LEFT (1 << 3)
# define TOKS_RIGHT (1 << 4)
# define TOKS_IDENT (1 << 5)
# define TOKS_POSTFIX (1 << 6)
# define TOKS_PREFIX (1 << 7)
# define TOKS_OPERATOR (1 << 8)

enum			e_tok
{
	TOK_END = '\0',
	TOK_HEREDOC = TOK_END + 1,
	TOK_RAOUT,
	TOK_LAMP,
	TOK_RAMP,
	TOK_CMP,
	TOK_EOL = '\n',
	TOK_PIPEAND = TOK_EOL + 1,
	TOK_AMPR,
	TOK_LAND,
	TOK_LOR,
	TOK_WORD,
	TOK_ASSIGN,
	TOK_FI,
	TOK_DONE,
	TOK_DRBRA,
	TOK_THEN,
	TOK_DO,
	TOK_ELIF,
	TOK_ELSE,
	TOK_IF,
	TOK_WHILE,
	TOK_DLBRA,
	TOK_HERENOW,
	TOK_FUNCTION,
	TOK_BANG = '!',
	TOK_AMP = '&',
	TOK_LPAR = '(',
	TOK_RPAR = ')',
	TOK_LCUR = '{',
	TOK_RCUR = '}',
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
}				t_tok;

extern t_bool	sh_tokidis(uint8_t id, uint16_t flags);
extern t_bool	sh_tokis(t_tok *tok, uint16_t flags);
extern char		*sh_tokstr(t_tok *tok);
extern t_tok	*sh_tokpeek(t_deq *toks);
extern t_tok	*sh_toknext(t_deq *toks);

#endif
