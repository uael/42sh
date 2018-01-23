/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:13:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_EDIT_SEARCH_H
# define LIBRL_EDIT_SEARCH_H

#include "../read.h"

static t_sds	g_lookup_stack = { 0, 0, 0 };
static t_sds	*g_lookup = &g_lookup_stack;
static t_editln	g_candidate_stack;
static t_editln	*g_candidate = &g_candidate_stack;
static t_ofs	g_edit_out_stack = {STDOUT_FILENO, 0, {0}};
static t_ofs	*g_out = &g_edit_out_stack;
static size_t	g_idx = 0;

void			searchprint(void);

#endif
