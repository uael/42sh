/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/hist.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 09:49:12 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_HIST_H
# define MSH_HIST_H

# include <libft.h>

# define HIST_MAX (100)

extern char		*sh_histadd(char const *ln, size_t len);
extern char		*sh_histcat(char const *ln, size_t len, char c, char **out);
extern t_bool	sh_histcpy(uint8_t id, t_sds *dest);

/*
** TODO load/save
*/

extern int		sh_histload(char const *filename);
extern int		sh_histsave(char const *filename);

#endif
