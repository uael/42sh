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
	MSH_TOK_LSH = MSH_TOK_END + 1,
	MSH_TOK_RSH,
	MSH_TOK_LAN,
	MSH_TOK_RAN,
	MSH_TOK_LSA,
	MSH_TOK_LRT,
	MSH_TOK_TAB = '\t',
	MSH_TOK_EOL = '\n',
	MSH_TOK_RPI = MSH_TOK_EOL + 1,
	MSH_TOK_DSC,
	MSH_TOK_AND,
	MSH_TOK_LOR,
	MSH_TOK_CAS,
	MSH_TOK_KDO,
	MSH_TOK_DNE,
	MSH_TOK_EIF,
	MSH_TOK_ELS,
	MSH_TOK_FUN,
	MSH_TOK_FOR,
	MSH_TOK_KFI,
	MSH_TOK_KIF,
	MSH_TOK_KIN,
	MSH_TOK_SAC,
	MSH_TOK_SEL,
	MSH_TOK_THN,
	MSH_TOK_UNT,
	MSH_TOK_WIL,
	MSH_TOK_NBR,
	MSH_TOK_WRD,
	MSH_TOK_SPC = ' ',
	MSH_TOK_NOT = '!',
	MSH_TOK_AMP = '&',
	MSH_TOK_LPR = '(',
	MSH_TOK_RPR = ')',
	MSH_TOK_HYP = '-',
	MSH_TOK_SCO = ';',
	MSH_TOK_LTH = '<',
	MSH_TOK_LET = '=',
	MSH_TOK_GTH = '>',
	MSH_TOK_LBR = '[',
	MSH_TOK_BSL = '\\',
	MSH_TOK_RBR = ']',
	MSH_TOK_LCR = '{',
	MSH_TOK_PIP = '|',
	MSH_TOK_RCR = '}',
};

extern t_bool	msh_lex(t_lexer *self);

#endif
