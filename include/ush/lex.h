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

# include "tok.h"

# define TOK_ISREDIR_1(ID) ((ID)==TOK_RIN||(ID)==TOK_ROUT)
# define TOK_ISREDIR_2(ID) ((ID)!=TOK_EOL&&((ID)>=TOK_HEREDOC&&(ID)<=TOK_AMPR))
# define TOK_ISREDIR(ID) (TOK_ISREDIR_1(ID)||TOK_ISREDIR_2(ID))
# define TOK_ISWORD(I) ((I)==TOK_WORD)
# define TOK_ISEND(ID) ((ID)==TOK_EOL||(ID)==TOK_END)
# define TOK_ISCMDM(ID) (TOK_ISWORD(ID)||TOK_ISREDIR(ID))
# define TOK_ISLFT(ID) ((ID)=='('||((ID)>=TOK_THEN&&(ID)<=TOK_DLBRA))
# define TOK_ISRGT(ID) ((ID)==')'||((ID)>=TOK_FI&&(ID)<=TOK_ELSE))

# define LEXE(ST, FD) ((ST) < 0 || (FD) < 0 || !g_sh->tty)
# define PAT(...) ((char []){__VA_ARGS__,'\0'})

# define TOKC_SEP ';','&'
# define TOKC_LOG TOK_LAND,TOK_LOR
# define TOKC_LFT '(',TOK_DLBRA,TOK_IF,TOK_ELSE,TOK_ELIF,TOK_THEN
# define TOKC_RGT ')',TOK_DRBRA,TOK_FI

# define TOKS_NOSOLO ((const char *)PAT(TOKC_SEP,'|',TOKC_LOG))
# define TOKS_RVAL ((const char *)PAT('|',TOKC_LOG,TOK_BANG))
# define TOKS_OPEN ((const char*)PAT(TOKC_LFT))
# define TOKS_CLOSE ((const char*)PAT(TOKC_RGT))
# define TOKS_OPENPRV ((const char*)PAT(TOKC_LFT,TOKC_SEP,'|','\n'))

typedef struct	s_src
{
	int			fd;
	char		**it;
	char		**ln;
}				t_src;

typedef int		(t_lexcb)(int fd, t_deq *toks, char **ln);

extern int		sh_lex(int fd, char **it, char **ln, t_lexcb *cb);
extern int		sh_lexline(t_src *src, t_deq *toks, t_bool new);
extern int		sh_tokenize(t_src *s, t_tok *tok);
extern int		sh_lexreduce(t_src *s, t_deq *toks, size_t from);
extern int		sh_lexcheck(t_src *s, t_deq *toks);
extern int		sh_lexdollar(t_src *s, t_tok *tok);
extern int		sh_lexop(t_src *s, t_tok *tok);
extern int		sh_lexbslash(t_src *src);
extern int		sh_lexword(t_src *s, t_tok *tok);
extern int		sh_lexheredoc(t_src *s, t_tok *tok);
extern t_bool	sh_isname(char *word);

#endif
