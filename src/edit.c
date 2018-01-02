/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/edit.h"

extern int		sh_editln(t_editln *ln, char *prompt, size_t plen)
{
	ssize_t		rd;
	char		key[6];

	(void)prompt;
	(void)plen;
	while ((rd = ft_read(STDIN_FILENO, key, 6)) > 0)
	{
		if (rd == 1 && (!ft_memcmp(key, "\xa", 1) || !ft_memcmp(key, "\xd", 1)))
			*key = '\n';
		ft_write(STDOUT_FILENO, key, (size_t)rd);
		ft_memcpy(ln->buf + ln->len, key, (size_t)rd);
		ln->len += rd;
		if (rd == 1 && *key == '\n')
			break ;
	}
	return (YEP);
}
