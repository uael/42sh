/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H

# include <string.h>

# include "tys.h"
# include "mem.h"

extern void		ft_bzero	(void *ptr, size_t n);

extern void		*ft_memccpy(void *d, void const *s, int c, size_t n);
extern void		*ft_memchr(void const *s, int c, size_t n);
extern int		ft_memcmp(void const *a, void const *b, size_t n);
extern void		*ft_memcpy(void *dst, void const *src, size_t n);
extern void		*ft_memmove(void *dst, void const *src, size_t len);
extern void		*ft_memrcpy(void *dst, void const *src, size_t n);
extern void		*ft_memset(void *b, int c, size_t len);

extern char		*ft_strbegw(char const *s1, char const *s2);
extern char		*ft_strcat(char *dest, char const *src);
extern char		*ft_strchr(char const *s, int c);
extern char		*ft_strmchr(char const *s, char const *c);
extern int		ft_strcmp(char const *s1, char const *s2);
extern void		ft_strclr(char *s);
extern char		*ft_strcpy(char *dest, char const *src);
extern char		*ft_strdup(char const *src);
extern size_t	ft_strlen(char const *str);
extern size_t	ft_strlcpy(char *dst, char const *src, size_t size);
extern size_t	ft_strlcat(char *dest, char const *src, size_t size);
extern uint8_t	ft_strnbr(char *dst, int64_t n, uint8_t base);
extern char		*ft_strncat(char *dest, char const *src, size_t nb);
extern int		ft_strncmp(char const *s1, char const *s2, size_t n);
extern char		*ft_strncpy(char *dest, char const *src, size_t n);
extern size_t	ft_strnlen(char const *str, size_t size);
extern char		*ft_strnstr(char const *str, char const *f, size_t l);
extern char		*ft_strrchr(char const *s, int c);
extern char		**ft_strsplit(char const *s, char c);
extern char		*ft_strstr(char const *haystack, char const *needle);
extern size_t	ft_strword(char const *s, char c, char e);

#endif
