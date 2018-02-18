/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/word.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/18 17:29:12 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_WORD_H
# define USH_WORD_H

# include "libft/ft_glob.h"
# include "var.h"
# include "tok.h"

# define WORD_SQUOTE (1 << 1)
# define WORD_DQUOTE (1 << 2)
# define WORD_BQUOTE (1 << 3)
# define WORD_EXPLODE (1 << 4)

extern void		sh_wordexplode(T_GLOB *av, char const *src, size_t n);
extern size_t	sh_wordresolve(t_sds *d, char const *s, size_t n, uint8_t *e);

#endif
