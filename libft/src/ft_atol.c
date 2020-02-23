/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 22:31:46 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/07 12:16:09 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(char *str)
{
	long	nbr;
	long	dir;

	nbr = 0;
	dir = 1;
	if (*str == 0)
		return (0);
	while (*str == '\f' || *str == ' ' || *str == '\n' || *str == '\r' \
			|| *str == '\v' || *str == '\t')
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			dir *= -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * dir);
}
