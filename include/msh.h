/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <libft.h>

enum		e_msh_tok
{
	MSH_TOK_END = '\0',
	MSH_TOK_LSHIFT = MSH_TOK_END + 1,
	MSH_TOK_RSHIFT,
	MSH_TOK_LAMP,
	MSH_TOK_RAMP,
	MSH_TOK_CMP,
	MAH_TOK_RARROW,
	MSH_TOK_TAB = '\t',
	MSH_TOK_EOL = '\n',
	MSH_TOK_RPIPE = MSH_TOK_EOL + 1,
	MSH_TOK_AMPR,
	MSH_TOK_LAND,
	MSH_TOK_LOR,
	MSH_TOK_CASE,
	MSH_TOK_DO,
	MSH_TOK_DONE,
	MSH_TOK_ELIF,
	MSH_TOK_ELSE,
	MSH_TOK_FUNCTION,
	MSH_TOK_FOR,
	MSH_TOK_FI,
	MSH_TOK_IF,
	MSH_TOK_IN,
	MSH_TOK_ESAC,
	MSH_TOK_SELECT,
	MSH_TOK_THEN,
	MSH_TOK_UNTIL,
	MSH_TOK_WHILE,
	MSH_TOK_NUM,
	MSH_TOK_WORD,
	MSH_TOK_SPACE = ' ',
	MSH_TOK_NOT = '!',
	MSH_TOK_AMP = '&',
	MSH_TOK_LPAR = '(',
	MSH_TOK_RPAR = ')',
	MSH_TOK_HYPEN = '-',
	MSH_TOK_SEMICOLON = ';',
	MSH_TOK_LTH = '<',
	MSH_TOK_ASSIGN = '=',
	MSH_TOK_GTH = '>',
	MSH_TOK_LBRACKET = '[',
	MSH_TOK_LSLASH = '\\',
	MSH_TOK_RBRACKET = ']',
	MSH_TOK_LCURLY = '{',
	MSH_TOK_PIPE = '|',
	MSH_TOK_RCURLY = '}',
};

extern t_bool	msh_lex(t_lexer *self);

#endif
