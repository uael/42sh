/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/exp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_EXP_H
# define USH_EXP_H

# include <libft.h>

# define ACT_ISRP(A) ((A)=='#'||(A)=='L'||(A)=='%'||(A)=='R')
# define ACT_ISNULL(A) ((A)=='?'||(A)=='-'||(A)=='=')

extern char		*g_ifs;
extern char		g_ifsw[4];
extern char		*g_origin;

enum e_act
{
	ACT_NONE = 0,
	ACT_RP_SHORT_LEFT = '#',
	ACT_RP_LONG_LEFT = 'L',
	ACT_RP_SHORT_RIGHT = '%',
	ACT_RP_LONG_RIGHT = 'R',
	ACT_NULL_ERROR = '?',
	ACT_NULL_SUBST = '-',
	ACT_NONNULL_SUBST = '+',
	ACT_NULL_ASSIGN = '='
};

typedef struct	s_param
{
	t_bool		brace : 1;
	t_bool		special : 1;
	t_bool		hash : 1;
	t_bool		colon : 1;
	t_bool		quoted : 1;
	char		*start;
	t_sds		env;
	t_sds		pattern;
	enum e_act	act;
}				t_param;

extern int		sh_expwords(t_vec *av, char const *src, size_t n);
extern int		sh_expword(t_sds *word, char const *src, size_t n);
extern int		sh_exparith(t_sds *word, char **words, t_bool brackets);
extern int		sh_expbackslash(t_sds *word, char **words, t_bool quote);
extern int		sh_expbacktick(t_sds *word, char **words, t_vec *av);
extern int		sh_expbrace(t_sds *word, char **words, t_vec *av);
extern int		sh_expcomm(t_sds *word, char **words, t_vec *av);
extern int		sh_expcommexec(t_sds *word, t_sds *comm, t_vec *av);
extern int		sh_expdollars(t_sds *word, char **words, t_vec *av, char quote);
extern int		sh_expglob(t_sds *word, char **words, t_vec *av);
extern int		sh_expparam(t_sds *w, char **words, t_vec *av, t_bool quoted);
extern int		sh_expparamsubst(t_sds *w, char **words, t_vec *av, t_param *p);
extern int		sh_expparamdone(t_param *param, int st, char *value, t_bool f);
extern int		sh_expparamenv(t_sds *w, char **words, t_vec *av, t_param *p);
extern int		sh_expparampattern(t_sds *w, char **ws, t_vec *a, t_param *p);
extern int		sh_expdquote(t_sds *word, char **words, t_vec *av);
extern int		sh_expsquote(t_sds *word, char **words);
extern int		sh_exptidle(t_sds *word, char **words, size_t wc);

#endif
