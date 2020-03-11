/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:17:24 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 20:14:14 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"
#include <sys/wait.h>

void	save_and_run(t_mini_exc *glob, char *line, t_plst **process)
{
	process[0] = new_process(glob, line);
	process[1] = process[0];
	while (process[1])
	{
		if (process[1]->ampersand == 0)
			mini_run_normal(glob, process[1]);
		if (process[1])
			process[1] = process[1]->next;
	}
	if (line && ft_strlen(line) > 0)
		update_history(glob, line);
	free_process(process);
	process[1] = NULL;
	signal(SIGINT, handle_sig_prnt);
	ft_putstr("$> ");
}

void	start_minishell(t_mini_exc *glob)
{
	t_plst	**process;
	char	*line;
	int		ret;

	ret = 0;
	line = NULL;
	process = (t_plst **)malloc(sizeof(t_plst *) * 2);
	init_proc(process, 2);
	while (1)
	{
		ft_putstr("$> ");
		ret = 1;
		while ((ret = get_next_line(1, &line)) > 0)
			save_and_run(glob, line, process);
		if (ret == 0)
			break ;
	}
}
