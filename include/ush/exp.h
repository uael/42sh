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

extern char		*g_ifs;
extern char		g_ifsw[4];

typedef struct	s_param
{
	t_bool		brace : 1;
	t_bool		special : 1;
	t_bool		hash : 1;
	t_bool		quoted : 1;
	t_bool		freev : 1;
	char		*start;
	char		*val;
	t_sds		env;
}				t_param;

typedef struct	s_range
{
	t_vec		av;
	t_bool		ascii : 1;
	int			range[3];
}				t_range;

extern int		sh_exp(char **words, t_sds *word, t_vec *av);
extern int		sh_expword(t_sds *word, char const *src, size_t n);
extern int		sh_expwords(t_vec *av, char const *src, size_t n);
extern int		sh_exparith(t_sds *word, char **words, t_bool brackets);
extern int		sh_exparitheval(char *expr, long int *result);
extern int		sh_expbackslash(t_sds *word, char **words, t_bool quote);
extern int		sh_expbacktick(t_sds *word, char **words, t_vec *av);
extern int		sh_expbrace(t_sds *word, char **w, t_vec *av);
extern int		sh_expcomm(t_sds *word, char **words, t_vec *av);
extern int		sh_expcommexec(t_sds *word, t_sds *comm, t_vec *av);
extern void		sh_expcommread(int fd, t_sds *word, t_vec *av);
extern int		sh_expdollars(t_sds *word, char **words, t_vec *av, char quote);
extern int		sh_expglob(t_sds *word, char **words, t_vec *av);
extern int		sh_expparam(t_sds *w, char **words, t_vec *av, t_bool quoted);
extern int		sh_expparamsubst(t_sds *w, char **words, t_vec *av, t_param *p);
extern int		sh_expparamval(t_sds *w, char **words, t_vec *av, t_param *p);
extern int		sh_expparamdone(t_param *param, int st);
extern int		sh_expparamenv(t_sds *w, char **words, t_vec *av, t_param *p);
extern int		sh_expdquote(t_sds *word, char **words, t_vec *av);
extern int		sh_expsquote(t_sds *word, char **words);
extern int		sh_exptilde(t_sds *word, char **words, size_t wc);

#endif
