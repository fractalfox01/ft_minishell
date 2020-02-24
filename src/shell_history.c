/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 11:16:22 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/23 16:40:26 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void    update_history(t_mini_exc *glob, char *line)
{
    size_t	i;
    char	**n_tab;

    i = 0;
    n_tab = NULL;
    while (glob->history[i])
        i++;
    if (i == glob->history_size)
    {
        glob->history_size *= 2;
        i = 0;
        n_tab = (char **)malloc(sizeof(char *) * (glob->history_size));
        while (glob->history[i])
        {
            n_tab[i] = ft_strdup(glob->history[i]);
            ft_strdel(&(glob->history[i]));
            i++;
        }
        n_tab[i++] = ft_strdup(line);
        while (i < glob->history_size)
            n_tab[i++] = NULL;
    }
    else
        glob->history[i] = ft_strdup(line);
}