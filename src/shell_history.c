/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 11:16:22 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 20:23:00 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void    increase_history_size(t_mini_exc *glob, char *line, char ***n_tab)
{
    size_t i;

    i = 0;
    glob->history_size *= 2;
    n_tab[0] = (char **)malloc(sizeof(char *) * (glob->history_size + 1));
    while (glob->history[i])
    {
        n_tab[0][i] = ft_strdup(glob->history[i]);
        ft_strdel(&(glob->history[i]));
        i++;
    }
    n_tab[0][i++] = ft_strdup(line);
    while (i < (glob->history_size + 1))
        n_tab[0][i++] = NULL;
    free(*glob->history);
}

void    update_history(t_mini_exc *glob, char *line)
{
    size_t	i;
    char	**n_tab;

    i = 0;
    n_tab = NULL;
    i = ft_2dlen(glob->history);
    if (i >= glob->history_size)
    {
        increase_history_size(glob, line, &n_tab);
		glob->history = ft_2d_tab(glob->history_size);
		while (n_tab[i])
		{
			glob->history[i] = ft_strdup(n_tab[i]);
			ft_strdel(&n_tab[i]);
			i++;
		}
		free(*n_tab);
		n_tab = NULL;
		while (i < (glob->history_size + 1))
			glob->history[i++] = NULL;
    }
    else
        glob->history[i] = ft_strdup(line);
}