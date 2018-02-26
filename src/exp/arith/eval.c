/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/arith/eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

static long	atoio(char *str, char **eptr)
{
	long	result;
	char	sign;

	result = 0;
	while (ft_isspace(*str))
		++str;
	if ((sign = *str) == '+' || sign == '-')
		++str;
	while (ft_isdigit(*str))
		result = result * 10 + *str++ - '0';
	if (eptr)
		*eptr = str;
	return ((int64_t)(sign == '-' ? -result : result));
}

static int	evalval(char **expr, long int *result)
{
	char *digit;

	digit = *expr;
	while (digit && *digit && ft_isspace(*digit))
		++digit;
	if (digit && *digit == '(')
	{
		++digit;
		while (**expr && **expr != ')')
			++(*expr);
		if (!**expr)
			return (NOP);
		*(*expr)++ = 0;
		if (sh_exparitheval(digit, result))
			return (NOP);
		return (YEP);
	}
	*result = atoio(digit, expr);
	if (digit == *expr)
		return (NOP);
	return (YEP);
}

static int	evaldiv(char **expr, long int *r)
{
	long int a;

	if (evalval(expr, r))
		return (NOP);
	while (**expr)
	{
		while (*expr && **expr && ft_isspace(**expr))
			++(*expr);
		if (**expr == '*' && ++(*expr))
		{
			if (evalval(expr, &a))
				return (NOP);
			*r *= a;
		}
		else if (**expr == '/' && ++(*expr))
		{
			if (evalval(expr, &a) || a == 0 || (a == -1 && *r == LONG_MIN))
				return (NOP);
			*r /= a;
		}
		else
			break ;
	}
	return (YEP);
}

int			sh_exparitheval(char *expr, long int *result)
{
	long int arg;

	if (evaldiv(&expr, result))
		return (NOP);
	while (*expr)
	{
		while (expr && *expr && ft_isspace(*expr))
			++expr;
		if (*expr == '+' && ++expr)
		{
			if (evaldiv(&expr, &arg))
				return (NOP);
			*result += arg;
		}
		else if (*expr == '-' && ++expr)
		{
			if (evaldiv(&expr, &arg))
				return (NOP);
			*result -= arg;
		}
		else
			break ;
	}
	return (YEP);
}
