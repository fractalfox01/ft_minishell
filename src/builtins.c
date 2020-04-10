/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 10:47:56 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 19:17:53 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		run_builtin(t_mini_exc *glob, t_plst *node)
{
	if (glob)
	{
		// do nothing
	}
	if (ft_strcmp(node->path, "exit") == 0)
		mini_shutdown(glob, node);
	else if (ft_strcmp(node->path, "cd") == 0)
		mini_changedir(glob, node);
	else if (ft_strcmp(node->path, "env") == 0)
		mini_print_env(glob);
	else if (ft_strcmp(node->path, "setenv") == 0)
		mini_set_env(glob, node);
	else if (ft_strcmp(node->path, "echo") == 0)
		mini_echo(glob, node);
	else if (ft_strcmp(node->path, "unsetenv") == 0)
		mini_unset_env(glob, node);
	else if (ft_strcmp(node->path, "clear") == 0)
		mini_clear(glob, node);
	else if (ft_strcmp(node->path, "history") == 0)
		print_history(glob);
	else
		return (0);
	return (1);
}
