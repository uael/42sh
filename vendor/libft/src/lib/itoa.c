/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:56:04 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib.h"
#include "libft/int.h"

char	*ft_itoa(int64_t n, uint8_t base)
{
	uint8_t	i;
	char	*str;

	if (n >= 0)
		return (ft_utoa((uint64_t)n, base));
	if (base > 30)
		return (NULL);
	i = ft_intlen(n, base);
	str = ft_malloc((i + 2) * sizeof(char));
	i = ft_intstr(str, n, base);
	str[i] = '\0';
	return (str);
}

char	*ft_utoa(uint64_t n, uint8_t base)
{
	uint8_t	i;
	char	*str;

	if (base > 30)
		return (NULL);
	i = ft_uintlen(n, base);
	str = ft_malloc((i + 1) * sizeof(char));
	i = ft_uintstr(str, n, base);
	str[i] = '\0';
	return (str);
}
