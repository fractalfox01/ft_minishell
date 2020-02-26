/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:17:24 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/25 16:59:14 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"
#include <sys/wait.h>

void	start_minishell(t_mini_exc *glob)
{
	t_plst	*process;
	t_plst	*tmp;
	char	*line;
	int		ret;
	int		i;
	int		count = 0;

	i = 0;
	ret = 0;
	line = NULL;
	process = NULL;
	tmp = NULL;
	while (1 && glob && count < 10)
	{
		count++;
		ft_putstr("$> ");
		ret = 1;
		while ((ret = get_next_line(1, &line)) >= 0)
		{
			if (ret == 1)
			{
				process = new_process(line);
				tmp = process;
				while (tmp)
				{
					update_history(glob, line);
					glob->pid = fork();
					if (glob->pid == 0)
						execve(tmp->path, tmp->argv, tmp->envp);
					else if (glob->pid < 0)
						perror("Process Failed");
					else
						waitpid(glob->pid, &glob->status, WUNTRACED);
					close(glob->pid);
					tmp = tmp->next;
				}
				free_process(&process);
				tmp = NULL;
			}
			else
				if (line)
					ft_strdel(&line);
			break ;
		}
	}
}