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

inline void	sh_wordexplode(t_vec *av, char const *src, size_t n)
{
	uint8_t	e;
	t_sds	word;
	char	*beg;
	char	*eol;
	char	sep[20];

	if (!(e = 0) && !sh_wordresolve(&word, src, n, &e))
		return ;
	if (!(e & WORD_EXPLODE))
		beg = word.buf;
	else
	{
		ft_strcat(ft_strcpy(sep, sh_varifs()), "\n");
		beg = word.buf;
		while ((eol = ft_strmchr(beg, sep)))
		{
			*eol = '\0';
			*(char **)ft_vecpush(av) = beg == word.buf ? beg :
				ft_strndup(beg, eol - beg);
			while (*++eol && ft_strchr(sep, *eol))
				;
			beg = eol;
		}
	}
	*(char **)ft_vecpush(av) = beg == word.buf ? beg : ft_strdup(beg);
}
