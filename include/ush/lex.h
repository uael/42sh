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
# define TOK_ISSEP(ID) ((ID)==TOK_SEMICOLON||(ID)==TOK_AMP)
# define TOK_ISCMDM(ID) (TOK_ISWORD(ID)||TOK_ISREDIR(ID))
# define LEX_SHOWE(ST, FD) ((ST) < 0 || (FD) < 0 || !g_sh->tty)

typedef struct	s_tokit
{
	char		**it;
	char		**ln;
}				t_tokit;

typedef int		(t_tokcb)(int fd, t_deq *toks, char **ln);

extern int		sh_lex(int fd, char **it, char **ln, t_tokcb *cb);
extern int		sh_lexvar(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexop(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexbslash(int fd, char **it, char **ln);
extern int		sh_lexword(int fd, t_tok *tok, char **it, char **ln);
extern int		sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln);
extern t_bool	sh_isname(char *word);

#endif
