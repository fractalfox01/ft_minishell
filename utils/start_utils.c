/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:42:07 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 13:36:11 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		check_if_builtin(char *path)
{
	if (path)
	{
		if (ft_strcmp(path, "exit") == 0)
			return (1);
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

int		test_if_executable(t_mini_exc *glob, t_plst *node)
{
	int			status;
	struct stat	st;

	status = 0;
	st.st_mode = 0;
	if (access(node->path, X_OK) == 0)
	{
		glob->pid = fork();		
		if (glob->pid == 0)
			execve(node->path, node->argv, node->envp);
		else if (glob->pid < 0)
			ft_putstr_fd("Ft_minishell: Error executing binaray file:\n", 2);
		else if (glob->pid)
			waitpid(glob->pid, &status, WUNTRACED);
		if (status)
		{
			ft_putstr_fd("Ft_minishell: process returned error: ", 2);
			ft_putnbr_fd(status, 2);
			ft_putstr_fd("\n", 2);
		}
		return (1);
	}
	lstat(node->path, &st);
	if (S_ISREG(st.st_mode))
	{
		ft_putstr_fd("Ft_minishell: Permission Denied:\n", 2);
		return (1);
	}
	return (0);
}

void	mini_run_normal(t_mini_exc *glob, t_plst *node)
{
	if ((check_if_builtin(node->path) == 0) && node->status)
	{
		glob->pid = fork();
		if (glob->pid == 0)
			execve(node->path, node->argv, glob->envp);
		else if (glob->pid < 0)
			ft_putstr_fd("Ft_minishell: Process Failed", 2);
		else
			waitpid(glob->pid, &glob->status, WUNTRACED);
	}
	else
	{
		if ((run_builtin(glob, node) == 0))
		{
			if ((ft_strlen(node->path) >= 2) && (node->path[0] == '.' && node->path[1] == '/'))
			{
				if (test_if_executable(glob, node) == 0)
				{
					ft_putstr_fd("Ft_minishell: Not an executable:\n", 2);
				}
			}
			else
				ft_putstr_fd("Ft_minishell: Command not found:\n", 2);
		}
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
	if (sig == 2)
	{
		ft_putstr_fd("Ft_minishell: SIGINT: stopping child proccess\n", 2);
	}
	if (sig == 18)
		ft_putstr("Ft_minishell: SIGTSTP: Ctrl-D stopping child proccess\n");
	return ;
}

void	handle_sig_chld(int sig)
{
	// printf("SIGNAL CAUGHT: child%d\n", sig);
	if (sig == 2)
	{
		ft_putstr_fd("Ft_minishell: SIGINT: stopping child proccess\n", 2);
	}
	if (sig == 18)
		ft_putstr("Ft_minishell: SIGTSTP: Ctrl-D stopping child proccess\n");
	return ;
}