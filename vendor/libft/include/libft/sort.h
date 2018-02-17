/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/13 01:15:44 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SORT_H
# define LIBFT_SORT_H

# include <string.h>

typedef unsigned char	t_uchar;
typedef int				t_ncmp(const void *a, const void *b, size_t n);

/*
** famous Ziggerman's Open Boards sort algorithm, also known as shell-sort
**
** length = length of the array
** n = sizeof(*array)
*/
void					ft_shellsort(void *arr, size_t length, \
							size_t sizeof_element, t_ncmp *cmp);

#endif
