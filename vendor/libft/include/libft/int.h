/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:29:15 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_INT_H
# define LIBFT_INT_H

# include "tys.h"

extern uint8_t	ft_intlen(int64_t n, uint8_t base);
extern uint8_t	ft_floatlen(float n, int precision, uint8_t base);
extern uint8_t	ft_uintlen(uint64_t n, uint8_t base);
extern uint8_t	ft_floatstr(char *dst, double n, int precision, uint8_t base);
extern uint8_t	ft_intstr(char *dst, int64_t n, uint8_t base);
extern uint8_t	ft_uintstr(char *dst, uint64_t n, uint8_t base);

#endif
