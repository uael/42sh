/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str/str_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

static char const		*g_s;
static unsigned long	g_cutoff;
static int				g_cutlim;

static inline void		updateacc(unsigned long *acc, int *any, int base)
{
	int c;

	while ((c = *g_s++))
	{
		if (ft_isdigit(c))
			c -= '0';
		else if (ft_isalpha(c))
			c -= ft_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (*any < 0 || *acc > g_cutoff || (*acc == g_cutoff && c > g_cutlim))
			*any = -1;
		else
		{
			*any = 1;
			*acc *= base;
			*acc += c;
		}
	}
}

static inline long		cutoff(const char *nptr, char **eptr, int base, int neg)
{
	unsigned long	acc;
	int				any;

	g_cutoff = (unsigned long)(neg ? -(unsigned long)LONG_MIN : LONG_MAX);
	g_cutlim = (int)(g_cutoff % (unsigned long)base);
	g_cutoff /= (unsigned long)base;
	acc = 0;
	any = 0;
	updateacc(&acc, &any, base);
	if (any < 0)
	{
		acc = (unsigned long)(neg ? LONG_MIN : LONG_MAX);
		errno = ERANGE;
	}
	else if (neg)
		acc = (unsigned long)-acc;
	if (eptr != 0)
		*eptr = (char *) (any ? g_s - 1 : nptr);
	return (acc);
}

inline long				ft_strtol(const char *nptr, char **eptr, int base)
{
	int			c;
	int			neg;

	neg = 0;
	g_s = nptr;
	while (ft_isspace(c = *g_s++))
		;
	if (c == '-')
	{
		neg = 1;
		c = *g_s++;
	} else if (c == '+')
		c = *g_s++;
	if ((base == 0 || base == 16) && c == '0' && (*g_s == 'x' || *g_s == 'X'))
	{
		c = g_s[1];
		g_s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	return (cutoff(nptr, eptr, base, neg));
}

