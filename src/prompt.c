/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/shell.h"

static char		*promptreduce(char *p, char *r, char *home)
{
	while (*p)
		if (*p == '/' && *(p + 1) && (home = ft_strchr(p + 1, '/')))
		{
			*r++ = *p++;
			*r++ = *p;
			p = home;
		}
		else
			*r++ = *p++;
	return (r);
}

inline char		*sh_prompt(char *prompt, char *buf)
{
	size_t	l;
	char	cwd[PATH_MAX + 1];
	char	*p;
	char	*r;
	char	*home;

	if (!(p = getcwd(cwd, PATH_MAX)))
	{
		THROW(WUT);
		return (NULL);
	}
	if ((home = sh_getenv("HOME")) && ft_strbegw(home, p))
	{
		if (p[l = ft_strlen(home)] != '\0')
			ft_memmove(p + 1, p + l, (ft_strlen(p) - l + 1) * sizeof(char));
		else
			p[1] = '\0';
		*p = '~';
	}
	r = buf;
	ft_strcpy(promptreduce(p, r, home), prompt);
	return (buf);
}
