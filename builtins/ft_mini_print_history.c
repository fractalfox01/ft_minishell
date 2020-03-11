/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_print_history.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:55:27 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 20:43:06 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		ft_nbrlen(int nbr)
{
	int	count;

	count = 0;
	while ((nbr % 10) >= 0)
	{
		nbr /= 10;
		count++;
		if (nbr == 0)
			break;
	}
	return (count);
}

void	print_history(t_mini_exc *glob)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (glob->history[i])
	{
		ft_putnbr(i);
		len = ft_nbrlen(i);
		if (len == 1)
			ft_putstr("   ");
		else if (len == 2)
			ft_putstr("  ");
		else
			ft_putstr(" ");
		ft_putstr(glob->history[i]);
		ft_putchar('\n');
		i++;
	}
}
