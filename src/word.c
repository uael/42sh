/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/word.h"

/*
** TODO: Handle pathname expansion
**
*/

inline void		expandvar(t_sds *word)
{
	char		*var;
	char		*end;
	t_bool		bracket;

	var = word->buf + 1;
	if ((bracket = (t_bool)(*var == '{')))
		++var;
	end = var;
	while (*end)
	{
		if (bracket && *end == '}')
			break ;
		++end;
	}
	*end = '\0';
	word->len = 0;
	if ((end = sh_varget(var)))
		ft_sdsapd(word, end);
	else
		*word->buf = '\0';
}

inline void		sh_wordglob(t_sds *word)
{
	(void)word;
}

inline void		sh_wordexpand(t_sds *word)
{
	if (*word->buf == '$')
		expandvar(word);
}
