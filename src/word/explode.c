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

#include <glob.h>

#include "ush/word.h"

#define _G_FLAGS (GLOB_BRACE | GLOB_TILDE | GLOB_APPEND | GLOB_NOCHECK)

inline void	sh_wordexplode(glob_t *av, char const *src, size_t n)
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
			glob(beg, _G_FLAGS, NULL, av) ? THROW(WUT) : 0;
			while (*++eol && ft_strchr(sep, *eol))
				;
			beg = eol;
		}
	}
	glob(beg, _G_FLAGS, NULL, av) ? THROW(WUT) : 0;
	free(word.buf);
}
