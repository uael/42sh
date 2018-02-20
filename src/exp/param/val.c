/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/param/done.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fnmatch.h>
#include <libps.h>

#include "ush/exp.h"
#include "ush/shell.h"

static char g_num[21];

static char	*itoaword(int n)
{
	uint8_t	l;

	l = ft_intstr(g_num, n, 10);
	g_num[l] = '\0';
	return (g_num);
}

static void	avword(t_param *p)
{
	size_t	len;
	char	*end;
	int		i;

	len = 0;
	i = 0;
	while (++i < g_sh->ac)
		len += ft_strlen(g_sh->av[i]) + 1;
	p->val = ft_malloc(len);
	end = p->val;
	*end = 0;
	i = 0;
	while (++i < g_sh->ac)
	{
		if (i > 1)
			*end++ = ' ';
		end = ft_stpcpy(end, g_sh->av[i]);
	}
	p->freev = 1;
}

static void	avwords(t_sds *word, t_vec *av, t_param *p)
{
	int		i;

	ft_sdsapd(word, g_sh->av[1]);
	*(char **)ft_vecpush(av) = ft_strdup(word->buf);
	word->len = 0;
	i = 1;
	while (++i < g_sh->ac - 1)
		*(char **)ft_vecpush(av) = ft_strdup(g_sh->av[i]);
	p->val = g_sh->av[i];
}

static int	special(t_sds *word, t_vec *av, t_param *p)
{
	uint8_t	l;

	if (*p->env.buf == '$')
		p->val = itoaword(g_sh->pid);
	else if (*p->env.buf == '!')
		p->val = itoaword(ps_lastpid());
	else if (*p->env.buf == '?')
		p->val = itoaword(g_sh->status);
	else if ((*p->env.buf == '*' || *p->env.buf == '@') && p->hash)
	{
		l = ft_intstr(g_num, g_sh->ac ? g_sh->ac - 1 : 0, 10);
		ft_sdsmpush(word, g_num, l);
		return (sh_expparamdone(p, 2));
	}
	else if (*p->env.buf == '*' || (*p->env.buf == '@' && !p->quoted))
		avword(p);
	else if (g_sh->ac == 2)
		p->val = g_sh->av[1];
	else if (g_sh->ac > 2)
		avwords(word, av, p);
	else
		return (sh_expparamdone(p, 2));
	return (YEP);
}

int			sh_expparamval(t_sds *word, char **words, t_vec *av, t_param *p)
{
	uint8_t	l;
	int		n;

	if (!p->env.len)
	{
		if (p->hash)
		{
			l = ft_intstr(g_num, g_sh->ac, 10);
			g_num[l] = '\0';
			p->val = g_num;
		}
		else if ((*words = p->start - 1))
		{
			*ft_sdspush(word) = '$';
			return (2);
		}
	}
	else if (ft_isdigit(*p->env.buf))
		p->val =
			(n = (int)ft_atoi(p->env.buf)) > g_sh->ac ? NULL : g_sh->av[n];
	else if (p->special)
		return (special(word, av, p));
	else
		p->val = sh_varget(p->env.buf, environ);
	return (YEP);
}
