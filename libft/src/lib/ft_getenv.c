/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 15:46:36 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib.h"
#include "libft/str.h"

inline char		*ft_getenv(char **env, char *var)
{
	char *val;

	while (*env && !ft_strbegw(var, *env))
		++env;
	if (!*env || !(val = ft_strchr(*env, '=')))
		return (NULL);
	return (val + 1);
}
