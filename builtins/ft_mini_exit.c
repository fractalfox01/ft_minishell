/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:33:16 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/10 14:58:02 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	mini_shutdown(t_mini_exc *glob, t_plst *node)
{
	glob->ampersand = 0;
	glob->dent = NULL;
	glob->dr = NULL;
	ft_free_2d(&glob->envp);
	ft_free_2d(&glob->history);
	glob->history_size = 0;
	glob->i = 0;
	glob->j = 0;
	glob->pid = 0;
	glob->status = 0;
	glob->wpid = 0;
	free_process(&node);
	printf("exiting ft_minshell\n\n\n");
	system("leaks ft_minishell");
	exit(0);
}
