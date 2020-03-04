/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:42:07 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/02 15:25:51 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int		check_if_builtin(char *path)
{
	if (path)
	{
		if (ft_strcmp(path, "exit") == 0)
			exit (0);
		if (ft_strcmp(path, "cd") == 0)
			return (1);
		if (ft_strcmp(path, "env") == 0)
			return (1);
		if (ft_strcmp(path, "setenv") == 0)
			return (1);
		if (ft_strcmp(path, "echo") == 0)
			return (1);
		if (ft_strcmp(path, "unsetenv") == 0)
			return (1);
		if (ft_strcmp(path, "clear") == 0)
			return (1);
		if (ft_strcmp(path, "history") == 0)
			return (1);
	}
	return (0);
}

void	mini_run_normal(t_mini_exc *glob, t_plst *node)
{
	if (check_if_builtin(node->path) == 0)
	{
		glob->pid = fork();
		if (glob->pid == 0)
			execve(node->path, node->argv, node->envp);
		else if (glob->pid < 0)
			perror("Process Failed");
		else
			waitpid(glob->pid, &glob->status, WUNTRACED);
	}
	else
	{
		run_builtin(glob, node);
	}
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
	glob->wpid = fork();
	if (glob->wpid == 0)
		execve(node->path, node->argv, node->envp);
	else if (glob->wpid < 0)
		perror("Process Failed");
	else if (glob->wpid > 0)
	{
		ft_putchar('[');
		ft_putnbr(glob->flag);
		ft_putstr("] ");
		ft_putnbr(glob->wpid);
		ft_putchar('\n');
	}
		// waitpid(glob->wpid, &glob->status, WUNTRACED);
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

void	handle_sig_prnt(int sig)
{
	// printf("SIGNAL CAUGHT: %d\n", sig);
	if (sig == 2)
	{
		ft_putstr("Stopping Process\n");
	}
	return ;
}

void	handle_sig_chld(int sig)
{
	if (sig == 2)
	{
		ft_putstr("Stopping Child Process\n");
	}
	return ;
}