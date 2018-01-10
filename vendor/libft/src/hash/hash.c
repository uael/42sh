/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 09:54:36 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/hash.h"

inline uint32_t	ft_ihash(int i)
{
	return (IHASH(i));
}

inline uint32_t	ft_uhash(unsigned int u)
{
	return (IHASH(u));
}

inline uint32_t	ft_lhash(long l)
{
	return (LHASH(l));
}

inline uint32_t	ft_ulhash(unsigned long ul)
{
	return (LHASH(ul));
}

inline uint32_t	ft_llhash(long long int ll)
{
	return (LLHASH(ll));
}
