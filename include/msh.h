/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
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
	MSH_TOK_RARROW,
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
	MSH_TOK_RBRACKET = ']',
	MSH_TOK_LCURLY = '{',
	MSH_TOK_PIPE = '|',
	MSH_TOK_RCURLY = '}',
};

#define MSH_EXIT(code, msh) exit(ft_dtor((code),(t_dtor)msh_dtor, msh, NULL))
#define CMD_NOK(msg) ft_dtor(RET_NOK, NULL, NULL, (msg))

extern t_ret	msh_lex(t_lexer *self);

typedef struct	s_msh
{
	t_lexer		lexer;
	t_dstr		out;
	t_dstr		err;
	t_vstr		env;
}				t_msh;

typedef t_ret	(*t_shrule)(t_msh *, t_tok *);
typedef t_ret	(*t_shcmd)(t_msh *, t_vstr *);

extern t_shrule	g_msh_rules[UINT8_MAX];

extern t_ret	msh_init_stream(t_msh *self, char **env, t_istream *stream);
extern t_ret	msh_init_file(t_msh *self, char **env, char const *filename);
extern t_ret	msh_init_str(t_msh *self, char **env, char const *str);
extern t_ret	msh_init_nstr(t_msh *self, char **env, char const *s, size_t n);
extern void		msh_dtor(t_msh *self);
extern t_tok	*msh_peek(t_msh *self);
extern t_tok	*msh_peekn(t_msh *self, size_t n);
extern t_tok	*msh_next(t_msh *self, t_tok **next);
extern t_tok	*msh_consume(t_msh *self, uint8_t id);

extern t_ret	msh(t_msh *self);
extern t_ret	msh_av(t_msh *self, t_vstr *av, char *exe);
extern t_ret	msh_prompt(t_msh *self, char *prompt);
extern t_ret	msh_exec(t_msh *self, t_tok *tok);
extern t_ret	msh_bi_echo(t_msh *self, t_vstr *av);
extern t_ret	msh_bi_cd(t_msh *self, t_vstr *av);
extern t_ret	msh_bi_setenv(t_msh *self, t_vstr *av);
extern t_ret	msh_bi_unsetenv(t_msh *self, t_vstr *av);
extern t_ret	msh_bi_env(t_msh *self, t_vstr *av);
extern t_ret	msh_bi_exit(t_msh *self, t_vstr *av);

extern t_ret	msh_initenv(t_msh *self, char **env);
extern char		**msh_getenv(t_msh *self, char *var);
extern t_ret	msh_setenv(t_msh *self, char *var, char *val);
extern t_ret	msh_unsetenv(t_msh *self, char *var);
extern t_ret	msh_path_lookup(t_msh *self, char *file, int mode, char *ret);

#endif
