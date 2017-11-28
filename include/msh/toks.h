/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/toks.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TOKS_H
# define MSH_TOKS_H

# include <libft.h>

enum		e_sh_tok
{
	SH_TOK_END = '\0',
	SH_TOK_LSHIFT = SH_TOK_END + 1,
	SH_TOK_RSHIFT,
	SH_TOK_LAMP,
	SH_TOK_RAMP,
	SH_TOK_CMP,
	SH_TOK_RARROW,
	SH_TOK_TAB = '\t',
	SH_TOK_EOL = '\n',
	SH_TOK_RPIPE = SH_TOK_EOL + 1,
	SH_TOK_AMPR,
	SH_TOK_LAND,
	SH_TOK_LOR,
	SH_TOK_CASE,
	SH_TOK_DO,
	SH_TOK_DONE,
	SH_TOK_ELIF,
	SH_TOK_ELSE,
	SH_TOK_FUNCTION,
	SH_TOK_FOR,
	SH_TOK_FI,
	SH_TOK_IF,
	SH_TOK_IN,
	SH_TOK_ESAC,
	SH_TOK_SELECT,
	SH_TOK_THEN,
	SH_TOK_UNTIL,
	SH_TOK_WHILE,
	SH_TOK_WORD,
	SH_TOK_SPACE = ' ',
	SH_TOK_NOT = '!',
	SH_TOK_AMP = '&',
	SH_TOK_LPAR = '(',
	SH_TOK_RPAR = ')',
	SH_TOK_HYPEN = '-',
	SH_TOK_SEMICOLON = ';',
	SH_TOK_LTH = '<',
	SH_TOK_ASSIGN = '=',
	SH_TOK_GTH = '>',
	SH_TOK_LBRACKET = '[',
	SH_TOK_RBRACKET = ']',
	SH_TOK_LCURLY = '{',
	SH_TOK_PIPE = '|',
	SH_TOK_RCURLY = '}',
};

extern t_st		sh_tok_word(t_tok *tok, char peek, t_src *src);
extern t_st		sh_tok_syntax(t_tok *tok, char peek, t_src *src);

#endif
