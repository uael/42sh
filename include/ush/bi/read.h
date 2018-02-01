/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/bi/read.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_BI_READ_H
# define USH_BI_READ_H

#include "libft.h"

# define BI_READLA		(1 << 0)
# define BI_READLD		(1 << 1)
# define BI_READLE		(1 << 2)
# define BI_READLI		(1 << 3)
# define BI_READLN		(1 << 4)
# define BI_READUN		(1 << 5)
# define BI_READLP		(1 << 6)
# define BI_READLR		(1 << 7)
# define BI_READLS		(1 << 8)
# define BI_READLT		(1 << 9)
# define BI_READLU		(1 << 10)
# define BI_READINTER	(1 << 11)

typedef	struct s_read		t_read;
typedef	struct s_readopt	t_readopt;

struct			s_read
{
	short		flag;
	char		**names;
	char		delim;
	int			nchars;
	char		*prompt;
	int			timeout;
	int			fd;
	t_sds		input;
};

struct termios	sh_bireadterm(int init);

int				sh_bireadterminit(t_read *data);
int				sh_bireadexit(t_read *data);

int				sh_bireadgetdelim(char *optarg, t_read *data);
int				sh_bireadgetnchars(char *optarg, t_read *data);
int				sh_bireadgetprompt(char *optarg, t_read *data);
int				sh_bireadgettimeout(char *optarg, t_read *data);
int				sh_bireadgetfd(char *optarg, t_read *data);

#endif
