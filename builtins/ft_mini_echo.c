/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:56:40 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 14:57:34 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	mini_echo(t_mini_exc *glob, t_plst *node)
{
	int	i;

	i = 1;
	while (node->argv[i] && glob)
	{
		ft_putstr(node->argv[i++]);
		if (node->argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}
