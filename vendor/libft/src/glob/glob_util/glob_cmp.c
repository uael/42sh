/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:18:24 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/22 20:18:53 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

int		super_cmp(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(*(char **)a, *(char **)b));
}
