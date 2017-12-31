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

#include <stdio.h>

#include "msh/edit.h"

extern int		sh_editln(t_histln *ln, char *prompt, size_t plen)
{
	ssize_t			rd;
	char			key[6];

	(void)prompt;
	(void)plen;
	while ((rd = ft_read(STDIN_FILENO, key, 6)) > 0)
	{
		ft_write(STDOUT_FILENO, key, (size_t)rd);
		ft_memcpy(ln->edit.buf + ln->edit.len, key, (size_t)rd);
		ln->edit.len += rd;
	}
	return (YEP);
}
