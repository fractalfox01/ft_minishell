/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:17:24 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/03 12:11:49 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"
#include <sys/wait.h>

void	start_minishell(t_mini_exc *glob)
{
	t_plst	**process;
	char	*line;
	int		ret;
	int		count = 0;

	ret = 0;
	line = NULL;
	process = (t_plst **)malloc(sizeof(t_plst *) * 2);
	init_proc(process, 2);
	// envp stored in glob now
	while (1)
	{
		count++;
		ft_putstr("$> ");
		ret = 1;
		while ((ret = get_next_line(1, &line)) > 0)
		{
			if (ret == 1)
			{
				process[0] = new_process(glob, line);
				process[1] = process[0];
				while (process[1])
				{
					update_history(glob, line);
					if (process[1]->ampersand == 0)
						mini_run_normal(glob, process[1]);
					if (process[1])
						process[1] = process[1]->next;
				}
				free_process(process);
				process[1] = NULL;
			}
			else
				if (line)
					ft_strdel(&line);
			signal(SIGINT, handle_sig_prnt);
			// signal(SIGCHLD, handle_sig_chld);
			flag = 1;
			ft_putstr("$> ");
		}
		if (ret == 0)
			break ;
	}
}
