/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/utf8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../edit.h"

#define UNI "\xe2\x9d\xaf"

inline int	rl_wstrlen(char *str)
{
	int i;
	int ix;
	int q;

	q = 0;
	i = 0;
	ix = (int)ft_strlen(str);
	while (i < ix)
	{
		++q;
		if (*(str + i) == '\033')
		{
			while (*(str + ++i - 1) != 'm')
				;
			--q;
		}
		else if (!ft_strncmp(UNI, str + i, sizeof(UNI) - 1))
			i += sizeof(UNI) - 1;
		else
			++i;
	}
	return (q);
}
