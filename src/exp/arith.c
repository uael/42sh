/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/arith.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

static char	g_result[21];
static int	g_depth;

static int	arithdone(t_sds *expr, int st)
{
	ft_sdsdtor(expr);
	return (st);
}

static int	aritheval(t_sds *word, char **words, t_sds *expr, t_bool bracket)
{
	uint8_t			l;
	long int		result;
	long long int	tme;

	result = 0;
	if (bracket)
	{
		if (expr->len && sh_exparitheval(expr->buf, &result))
			return (arithdone(expr, NOP));
		l = ft_intstr(g_result, result, 10);
		g_result[l] = '\0';
		ft_sdsmpush(word, g_result, l);
		return (arithdone(expr, 2));
	}
	++*words;
	if (expr->len && sh_exparitheval(expr->buf, &result))
		return (arithdone(expr, NOP));
	if (result < 0 && (tme = -result))
		*ft_sdspush(word) = '-';
	else
		tme = result;
	l = ft_intstr(g_result, tme, 10);
	g_result[l] = '\0';
	ft_sdsmpush(word, g_result, l);
	return (arithdone(expr, 2));
}

static int	arithloop1(t_sds *word, char **words, t_sds *expr, t_bool brackets)
{
	if (**words == ')')
	{
		if (--g_depth == 0)
		{
			return (brackets || *(*words + 1) != ')' ? arithdone(expr, NOP)
				: aritheval(word, words, expr, 0));
		}
		*ft_sdspush(expr) = **words;
	}
	else if (**words == ']')
		return (brackets && g_depth == 1 ? aritheval(word, words, expr, 1) \
			: arithdone(expr, NOP));
	else if (**words == '(')
		++g_depth;
	else
		*ft_sdspush(expr) = **words;
	return (YEP);
}

static int	arithloop(t_sds *word, char **words, t_sds *expr, t_bool brackets)
{
	int st;

	if (**words == '$')
	{
		if ((st = sh_expdollars(expr, words, NULL, 1)))
			return (arithdone(expr, st));
	}
	else if (**words == '`' && (++*words))
	{
		if ((st = sh_expbacktick(expr, words, NULL)))
			return (arithdone(expr, st));
	}
	else if (**words == '\\')
	{
		if ((st = sh_expbackslash(expr, words, 1)))
			return (arithdone(expr, st));
	}
	else if (ft_strchr(";{}", **words))
		return (arithdone(expr, NOP));
	else
		return (arithloop1(word, words, expr, brackets));
	return (YEP);
}

int			sh_exparith(t_sds *word, char **words, t_bool brackets)
{
	int		st;
	t_sds	expr;

	*words -= (g_depth = 1);
	ft_sdsctor(&expr);
	while (*++*words)
		if ((st = arithloop(word, words, &expr, brackets)))
			return (st == 2 ? YEP : st);
	return (arithdone(&expr, NOP));
}
