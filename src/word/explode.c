/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word/resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/18 17:30:51 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_glob.h"
#include "ush/word.h"

#define _G_FLAGS (GLOBUX_BRACE | GLOBUX_TILDE | GLOBUX_APPEND | GLOBUX_NOCHECK)

inline void	sh_wordexplode(T_GLOB *av, char const *src, size_t n)
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
			DUMMY_GLOBCTOR(beg, _G_FLAGS, av) ? THROW(WUT) : 0;
			while (*++eol && ft_strchr(sep, *eol))
				;
			beg = eol;
		}
	}
	DUMMY_GLOBCTOR(beg, _G_FLAGS, av) ? THROW(WUT) : 0;
	free(word.buf);
}
