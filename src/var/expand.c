/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var/expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libps.h>

#include "ush/var.h"
#include "ush/shell.h"

static inline size_t	getvar(char const *from, char *to)
{
	t_bool	bracket;
	char	*beg;

	beg = to;
	if ((bracket = (t_bool)(*from == '{')))
		++from;
	if (*from == '_' || ft_isalpha(*from))
		while (*from && (*from == '_' || ft_isalnum(*from)) &&
			(!bracket || *from != '}'))
			*to++ = *from++;
	else if (ft_isdigit(*from))
		while (*from && ft_isdigit(*from))
			*to++ = *from++;
	else if (ft_strchr("#?$!", *from))
		*to++ = *from;
	else
		return (0);
	*to = '\0';
	return (to - beg + (bracket ? 2 : 0));
}

inline size_t			sh_varexpand(t_sds *dst, char const *src)
{
	char	var[PATH_MAX];
	char	buf[20];
	char	*val;
	size_t	len;
	int		n;

	len = getvar(src, var);
	if ((val = sh_varget(var, g_env)))
		ft_sdsapd(dst, val);
	else if (ft_isdigit(*var) && (n = (int)ft_atoi(var)) < g_sh->ac && n >= 0)
		ft_sdsapd(dst, g_sh->av[n]);
	else if ((len == 1 && ft_strchr("#?$!", *var)))
	{
		if (*var == '#')
			n = g_sh->ac;
		else if (*var == '?')
			n = g_sh->status;
		else if (*var == '$')
			n = g_sh->pid;
		else if (*var == '!')
			n = ps_lastpid();
		ft_sdsmpush(dst, buf, ft_intstr(buf, n, 10));
	}
	return (len);
}
