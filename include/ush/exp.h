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

extern char	*g_ifs;
extern char	g_ifsw[4];
extern char	*g_origin;

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

#define ACT_ISRP(A) ((A)=='#'||(A)=='L'||(A)=='%'||(A)=='R')
#define ACT_ISNULL(A) ((A)=='?'||(A)=='-'||(A)=='=')

typedef struct	s_param
{
	char		*start;
	t_bool		brace;
	t_bool		special;
	t_bool		hash;
	t_bool		colon;
	t_bool		quoted;
	t_sds		env;
	t_sds		pattern;
	enum e_act	act;
}				t_param;

extern int	sh_expwords(t_vec *av, char const *src, size_t n);
extern int	sh_expword(t_sds *word, char const *src, size_t n);
extern int	sh_exparith(t_sds *word, char **words, t_bool brackets);
extern int	sh_expbackslash(t_sds *word, char **words, t_bool quote);
extern int	sh_expbacktick(t_sds *word, char **words, t_vec *av);
extern int	sh_expbrace(t_sds *word, char **words, t_vec *av);
extern int	sh_expcomm(t_sds *word, char **words, t_vec *av);
extern int	sh_expcommexec(t_sds *word, t_sds *comm, t_vec *av);
extern int	sh_expdollars(t_sds *word, char **words, t_vec *av, char quote);
extern int	sh_expglob(t_sds *word, char **words, t_vec *av);
extern int	sh_expparam(t_sds *word, char **words, t_vec *av, t_bool quoted);
extern int	sh_expdquote(t_sds *word, char **words, t_vec *av);
extern int	sh_expsquote(t_sds *word, char **words);
extern int	sh_exptidle(t_sds *word, char **words, size_t wc);

#endif
