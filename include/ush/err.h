/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/err.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_ERR_H
# define USH_ERR_H

# include <libft.h>

struct s_tok;

extern int	sh_verr(char const *fmt, va_list ap);
extern int	sh_err(char const *fmt, ...);
extern int	sh_synerr(char const *ln, char const *it, char const *fmt, ...);
extern int	sh_parseerr(char const *ln, struct s_tok *t, char const *fmt, ...);

#endif
