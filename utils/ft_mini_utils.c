/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:45:14 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 15:56:32 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		ft_free_2d(char ***tab)
{
	int	i;

	i = 0;
	while (tab[0][i])
		ft_strdel(&(tab[0][i++]));
	free(*tab[0]);
	tab[0] = NULL;
	return (0);
}

int		ft_2dlen(char **tab)
{
	int	ret;

	ret = 0;
	while (tab[ret])
		ret++;
	return (ret);
}

char	**ft_2d_tab(size_t size)
{
	char	**ret;
	size_t	i;

	ret = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (ret)
	{
		while (i < size)
			ret[i++] = NULL;
		ret[i] = NULL;
		return (ret);
	}
	return (NULL);
}
