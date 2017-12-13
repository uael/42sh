/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/reduce.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 09:49:12 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_REDUCE_H
# define MSH_REDUCE_H

# include "sh.h"
# include "lex.h"

extern int	sh_reduce(t_sh *self);
extern int	sh_reduce_heredoc(t_sh *self, t_tok *tok);

#endif
