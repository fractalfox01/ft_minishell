/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:05:49 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/26 10:49:21 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	init_mini_glob(t_mini_exc *glob)
{
	glob->proc_tab = NULL;
	glob->i = 0;
	glob->history_size = 1000;
	glob->history = (char **)malloc(sizeof(char *) * glob->history_size);
	while (glob->i < 1000)
		glob->history[glob->i++] = NULL;
	glob->glob_pid = 0;
	glob->pid = 0;
	glob->wpid = 0;
	glob->ampersand = 0;
	glob->st.st_mode = 0;
	glob->dr = NULL;
	glob->dent = NULL;
	glob->i = 0;
	glob->j = 0;
	glob->status = 0;
	glob->flag = 0;
}