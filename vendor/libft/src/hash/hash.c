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

t_hasher const	g_ihash = { (t_hashfn *)ft_ihash, (t_eqfn *)ft_ieq };
t_hasher const	g_uhash = { (t_hashfn *)ft_uhash, (t_eqfn *)ft_ueq };
t_hasher const	g_lhash = { (t_hashfn *)ft_lhash, (t_eqfn *)ft_leq };
t_hasher const	g_ulhash = { (t_hashfn *)ft_ulhash, (t_eqfn *)ft_uleq };
t_hasher const	g_llhash = { (t_hashfn *)ft_llhash, (t_eqfn *)ft_lleq };
t_hasher const	g_ullhash = { (t_hashfn *)ft_ullhash, (t_eqfn *)ft_ulleq };
t_hasher const	g_szhash = { (t_hashfn *)ft_szhash, (t_eqfn *)ft_szeq };
t_hasher const	g_uszhash = { (t_hashfn *)ft_uszhash, (t_eqfn *)ft_uszeq };
t_hasher const	g_strhash = { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq };

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
