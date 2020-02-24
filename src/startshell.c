/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:17:24 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/23 11:28:21 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"
#include <sys/wait.h>

void	start_minishell(t_mini_exc *glob)
{
	t_plst	*process;
	char	*line;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	line = NULL;
	while (1 && glob)
	{
		ft_putstr("$> ");
		ret = 0;
		while ((ret = get_next_line(1, &line)) >= 0)
		{
			if (ret == 1)
			{
				update_history(glob, line);
				process = new_process(line);
				glob->pid = fork();
				if (glob->pid == 0)
					execve(process->path, process->argv, process->envp);
				else if (glob->pid < 0)
					perror("Process Failed");
				else if (glob->pid)
				{
					waitpid(glob->pid, &glob->status, WUNTRACED);
					free_process(&process);
					break ;
				}
			}
			else
				if (line)
					ft_strdel(&line);
			break ;
		}
	}
}