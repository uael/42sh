/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_H
# define LIBRL_H

# include <libft.h>
# include <term.h>
# include <termios.h>

# ifndef TTY
#  define TTY struct termios
# endif

/*
** TODO: hist load/save
** TODO: autocomplete api
*/

extern int		rl_histload(char const *filename);
extern int		rl_histsave(char const *filename);
extern char		*rl_histadd(char const *ln, size_t len);

extern int		rl_getline(int fd, char *prompt, char **ln);
extern int		rl_catline(int fd, char c, char **ln, char **it);
extern int		rl_reprint(void);
extern void		rl_finalize(int fd);
extern void		rl_dtor(void);

#endif
