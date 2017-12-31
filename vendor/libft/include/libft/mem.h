/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:57:12 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEM_H
# define LIBFT_MEM_H

# include "lib.h"

extern void	*ft_calloc(size_t sz);
extern void	*ft_malloc(size_t sz);
extern void	*ft_realloc(void const *ptr, size_t psz, size_t sz);

#endif
