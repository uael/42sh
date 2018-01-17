/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PARSE_H
# define USH_PARSE_H

# include "shell.h"
# include "pool.h"
# include "tok.h"

extern int		sh_parse(int fd, t_deq *toks, char **ln);
extern t_job	*sh_parselist(int fd, t_deq *toks, char **ln);
extern t_job	*sh_parseandor(int fd, t_deq *toks, char **ln);
extern t_job	*sh_parsepipeline(int fd, t_deq *toks, char **ln);
extern t_bool	sh_parsecommand(t_job *job, int fd, t_deq *toks, char **ln);

#endif
