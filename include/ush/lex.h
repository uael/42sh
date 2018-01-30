/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/lex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_LEX_H
# define USH_LEX_H

# include <librl.h>
# include "err.h"
# include "var.h"
# include "word.h"

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

# define ISREOL(IT) (*(IT) == '\n')
# define ISWEOL(IT) (*(IT) == '\r' && *((IT) + 1) == '\n')
# define ISEOL(IT) (ISREOL(IT) || ISWEOL(IT))

# define TOK_ISREDIR_1(ID) ((ID)==TOK_RIN||(ID)==TOK_ROUT)
# define TOK_ISREDIR_2(ID) ((ID)!=TOK_EOL&&((ID)>=TOK_HEREDOC&&(ID)<=TOK_AMPR))
# define TOK_ISREDIR(ID) (TOK_ISREDIR_1(ID)||TOK_ISREDIR_2(ID))
# define TOK_ISBOOL(ID) ((ID)==TOK_TRUE||(ID)==TOK_FALSE)
# define TOK_ISEND(ID) ((ID)==TOK_EOL||(ID)==TOK_END)

typedef struct	s_tok
{
	char		*val;
	size_t		cap;
	size_t		len;
	uint16_t	pos;
	uint8_t		id;
}				t_tok;

extern char		*sh_tokidstr(uint8_t id);
extern char		*sh_tokstr(t_tok *tok);

extern int		sh_lex(int fd, t_deq *toks, char **it, char **ln);
extern int		sh_lexvar(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexop(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexquote(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexbslash(int fd, char **it, char **ln);
extern int		sh_lexword(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexheredoct(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexreduce(int fd, t_deq *toks, char **it, char **ln);
extern int		sh_lexnext(int fd, t_deq *toks, char c, char **ln);
extern void		sh_tokexpand(t_tok *tok, t_deq *toks);
extern char		sh_rbracket(char b);
extern t_bool	sh_isname(char *word);

#endif
