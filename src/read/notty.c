/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read/notty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/resource.h>

#include "msh/read.h"

#ifndef OPEN_MAX
# define OPEN_MAX RLIMIT_NOFILE
#endif

static t_ifs	in[OPEN_MAX + 1] = { 0 };
static ssize_t	rd[OPEN_MAX + 1] = { 0 };

inline void		sh_nottyfinalize(int fd)
{
	ft_ifsclose(in + fd);
}

inline char		*sh_readnotty(int fd)
{
	char		*ln;

	if (fd <= 0 || fd > OPEN_MAX)
	{
		ENO_THROW(WUT, EINVAL);
		return (NULL);
	}
	if (rd[fd] > 0 && ft_ifsrd(in + fd, NULL, (size_t)rd[fd]) < 0)
		return (NULL);
	if ((rd[fd] = ft_ifschr(in + fd, 0, '\n', &ln)) > 0)
		return (ln);
	return (NULL);
}
