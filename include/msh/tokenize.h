/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/tokenize.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TOKENIZE_H
# define MSH_TOKENIZE_H

# include "read.h"

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
	TOK_SKIP,
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
	uint8_t		id;
	char		*val;
	size_t		len;
}				t_tok;

extern int		sh_tokenize(int fd, t_deq *toks, char *ln);

#endif
