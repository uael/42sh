/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/hash.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:54:24 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_HASH_H
# define LIBFT_HASH_H

# include "math.h"

# define IHASH(I) ((uint32_t)(I))
# if ULONG_MAX == UINT_MAX
#  define LHASH(L) IHASH(L)
# else
#  define LHASH(L) ((uint32_t)(((L)>>33^(L)^(L)<<11)))
# endif
# if ULLONG_MAX == ULONG_MAX
#  define LLHASH(LL) LHASH(LL)
# else
#  define LLHASH(LL) ((uint32_t)(((LL)>>33^(LL)^(LL)<<11)))
# endif
# if SIZE_MAX == UINT_MAX
#  define SZHASH(USZ) IHASH(USZ)
# elif SIZE_MAX == ULONG_MAX
#  define SZHASH(USZ) LHASH(USZ)
# else
#  define SZHASH(USZ) LLHASH(USZ)
# endif

typedef uint32_t		(t_hashfn)(void *x);

typedef struct			s_hasher
{
	t_hashfn			*hash;
	t_eqfn				*eq;
}						t_hasher;

extern const t_hasher	g_ihash;
extern const t_hasher	g_uhash;
extern const t_hasher	g_lhash;
extern const t_hasher	g_ulhash;
extern const t_hasher	g_llhash;
extern const t_hasher	g_ullhash;
extern const t_hasher	g_szhash;
extern const t_hasher	g_uszhash;
extern const t_hasher	g_strhash;

extern uint32_t			ft_ihash(int i);
extern uint32_t			ft_uhash(unsigned int u);
extern uint32_t			ft_lhash(long l);
extern uint32_t			ft_ulhash(unsigned long ul);
extern uint32_t			ft_llhash(long long int ll);
extern uint32_t			ft_ullhash(unsigned long long int ull);
extern uint32_t			ft_szhash(ssize_t sz);
extern uint32_t			ft_uszhash(ssize_t usz);
extern uint32_t			ft_strhash(char const *str);

#endif
