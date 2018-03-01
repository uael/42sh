/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/syn.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_SYN_H
# define USH_SYN_H

# include "lex.h"

extern int	sh_syncheck(t_src *s, t_deq *toks);
extern int	sh_synlist(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_synandor(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_synpipeline(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_syncmd(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_syncompoundcmd(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_synwhileclause(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_synifclause(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_syncompoundlist(t_src *s, t_deq *t, size_t *i, char const *e);
extern int	sh_synfuncdef(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_synterm(t_src *s, t_deq *toks, size_t *idx);
extern int	sh_synredir(t_src *src, t_deq *toks, size_t *idx);

#endif
