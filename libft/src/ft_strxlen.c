/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strxlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:54:20 by tvandivi          #+#    #+#             */
/*   Updated: 2019/09/23 14:23:45 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strxlen(const char *str, char c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0' && str[i] != c)
		{
			i++;
		}
	}
	return (i);
}