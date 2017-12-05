/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_caps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:11 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:37:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/trm.h"

inline char	*ft_caps_underline(void)
{
	return (tgetstr("us", NULL));
}

inline char	*ft_caps_rvideo(void)
{
	return (tgetstr("mr", NULL));
}

inline char	*ft_caps_reset(void)
{
	return (tgetstr("me", NULL));
}
