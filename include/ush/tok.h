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

# include <librl.h>
# include "err.h"
# include "var.h"
# include "word.h"

# define ISREOL(IT) (*(IT) == '\n')
# define ISWEOL(IT) (*(IT) == '\r' && *((IT) + 1) == '\n')
# define ISEOL(IT) (ISREOL(IT) || ISWEOL(IT))

enum			e_tok
{
	TOK_END = '\0',
	TOK_HEREDOC = TOK_END + 1,
	TOK_HEREDOCT,
	TOK_RAOUT,
	TOK_LAMP,
	TOK_RAMP,
	TOK_CMP,
	TOK_EOL = '\n',
	TOK_RPOUT = TOK_EOL + 1,
	TOK_AMPR,
	TOK_LAND,
	TOK_LOR,
	TOK_CASE,
	TOK_DO,
	TOK_DONE,
	TOK_ELIF,
	TOK_ELSE,
	TOK_FUNCTION,
	TOK_FOR,
	TOK_FI,
	TOK_IF,
	TOK_IN,
	TOK_ESAC,
	TOK_SELECT,
	TOK_THEN,
	TOK_UNTIL,
	TOK_WHILE,
	TOK_WORD,
	TOK_TRUE,
	TOK_FALSE,
	TOK_NOT = '!',
	TOK_AMP = '&',
	TOK_LPAR = '(',
	TOK_RPAR = ')',
	TOK_HYPEN = '-',
	TOK_SEMICOLON = ';',
	TOK_RIN = '<',
	TOK_ASSIGN = '=',
	TOK_ROUT = '>',
	TOK_LBRACKET = '[',
	TOK_RBRACKET = ']',
	TOK_LCURLY = '{',
	TOK_PIPE = '|',
	TOK_RCURLY = '}',
};

typedef struct	s_tok
{
	size_t		len;
	uint32_t	pos;
	uint8_t		id;
}				t_tok;

extern void		sh_tokdtor(t_tok *tok);
extern char		*sh_tokstr(t_tok *tok);
extern t_tok	*sh_tokpeek(t_deq *toks);
extern t_tok	*sh_toknext(t_deq *toks);
extern t_tok	*sh_tokpos(t_tok *tok, char const *it, char const *ln);

extern t_sds	*sh_tokdexpand(t_sds *dst, t_tok *src, char *ln);
inline size_t	sh_tokexpand(char *dst, t_tok *src, char *ln, size_t n);
extern void		sh_tokexplode(t_tok *tok, t_vec *av);

#endif
