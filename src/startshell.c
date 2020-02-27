/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:17:24 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/27 13:56:06 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"
#include <sys/wait.h>

void	mini_run_normal(t_mini_exc *glob, t_plst *node)
{
	glob->pid = fork();
	if (glob->pid == 0)
		execve(node->path, node->argv, node->envp);
	else if (glob->pid < 0)
		perror("Process Failed");
	else
		waitpid(glob->pid, &glob->status, WUNTRACED);
}

void	add_new_proc(t_mini_exc *glob)
{
	if (!(glob->proc_tab))
	{
		glob->proc_tab = (int **)malloc(sizeof(int *) * 1);
		glob->proc_tab[0][0] = glob->glob_pid; 
	}
}

void	mini_run_w_ampersand(t_mini_exc *glob, t_plst *node)
{

	glob->pid = fork();
	if (node->next)
		glob->wpid = fork();
	if ((glob->pid == 0) && (glob->wpid > 0))
		execve(node->path, node->argv, node->envp);
	else if ((glob->pid != 0) && (glob->wpid == 0))
	{
		if (node->next)
			execve(node->next->path, node->next->argv, node->next->envp);
	}
	else if (glob->pid < 0 || glob->wpid < 0)
		perror("Process Failed");
	else if (glob->wpid > 0)
		waitpid(glob->wpid, &glob->status, WUNTRACED);
}

void	init_proc(t_plst **procs, int amount)
{
	int	i;

	i = 0;
	if (procs)
	{
		while (i < amount)
			procs[i++] = NULL;
	}
	else
		procs = NULL;
}

void	handle_sig(int sig)
{
	if (sig == 2)
	{
		printf("SIGNAL CAUGHT: %d\n", sig);
	}
	return ;
}

void	start_minishell(t_mini_exc *glob)
{
	t_plst	**process;
	char	*line;
	int		ret;
	int		i;
	int		count = 0;

	i = 0;
	ret = 0;
	line = NULL;
	process = (t_plst **)malloc(sizeof(t_plst *) * 2);
	init_proc(process, 2);
	while (1 && glob)
	{
		count++;
		ft_putstr("$> ");
		ret = 1;
		while ((ret = get_next_line(1, &line)) >= 0)
		{
			if (ret == 1)
			{
				process[0] = new_process(line);
				process[1] = process[0];
				while (process[1])
				{
					update_history(glob, line);
					if (process[1]->ampersand == 0)
						mini_run_normal(glob, process[1]);
					else
					{
						mini_run_w_ampersand(glob, process[1]);
						process[1] = process[1]->next;
					}
					if (process[1])
						process[1] = process[1]->next;
				}
				free_process(&process[0]);
				process[1] = NULL;
			}
			else
				if (line)
					ft_strdel(&line);
			signal(SIGINT, handle_sig); 
			signal(SIGCHLD, handle_sig);
			break ;
		}
	}
}