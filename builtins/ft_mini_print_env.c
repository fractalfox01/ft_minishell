/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_print_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:08:03 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 15:08:24 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	mini_print_env(t_mini_exc *glob)
{
	int	i;

	i = 0;
	while (glob->envp[i])
	{
		ft_putstr(glob->envp[i++]);
		ft_putchar('\n');
	}
}
