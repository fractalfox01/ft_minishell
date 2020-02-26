/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:25:45 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/25 17:55:50 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int		max;
	char	**tab;

	if (s && c)
	{
		max = ft_wordcount((char *)s, c);
		tab = (char **)malloc(sizeof(s) * (max + 1));
		if (!(tab) || (max <= 0))
			return (NULL);
		tab = ft_strbuild(tab, s, c, max);
		return (tab);
	}
	else
	{
		tab = (char **)malloc(sizeof(s) * 1);
		tab[0] = ft_strdup(s);
		return (tab);
	}
	return (tab);
}
