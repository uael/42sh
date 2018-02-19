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

extern int	sh_wordexp(t_vec *av, char const *src, size_t n, t_bool quote);
extern int	sh_exparith(t_sds *word, char **words, t_bool brackets);
extern int	sh_expbackslash(t_sds *word, char **words, t_bool quote);
extern int	sh_expbacktick(t_sds *word, char **words, t_vec *av);
extern int	sh_expbrace(t_sds *word, char **words, t_vec *av);
extern int	sh_expcomm(t_sds *word, char **words, t_vec *av);
extern int	sh_expcommexec(t_sds *word, t_sds *comm, t_vec *av);
extern int	sh_expdollars(t_sds *word, char **words, t_vec *av, char quote);
extern int	sh_expglob(t_sds *word, char **words, t_vec *av);
extern int	sh_expparam(t_sds *word, char **words, t_vec *av, char quote);
extern int	sh_expdquote(t_sds *word, char **words, t_vec *av);
extern int	sh_expsquote(t_sds *word, char **words);
extern int	sh_exptidle(t_sds *word, char **words, size_t wc);

#endif
