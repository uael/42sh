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

extern char		*rl_readln(int fd, char *prompt);
extern char		*rl_readcat(int fd, char *prompt, char c, char **ln);
extern void		rl_readfinalize(int fd);
extern void		rl_readexit(int fd);

#endif
