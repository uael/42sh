/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word/resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/word.h"

inline size_t	sh_wordexplode(t_vec *av, char const *src, size_t n)
{
	uint8_t	e;
	t_sds	word;

	if (sh_wordresolve(&word, src, n, &e))
		*(char **)ft_vecpush(av) = word.buf;
	return (YEP);
}
