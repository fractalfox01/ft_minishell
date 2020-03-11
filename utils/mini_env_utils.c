/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:03:18 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 15:04:33 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	**copy_remainder(t_mini_exc *glob, int size)
{
	char	**tab;
	int		copy;
	int		len;
	int		i;

	i = 0;
	copy = size;
	while (glob->envp[size])
		size++;
	len = (size - copy);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!(tab))
		return (NULL);
	while (i < len)
		tab[i++] = ft_strdup(glob->envp[copy++]);
	tab[i] = NULL;
	return (tab);
}

char	*retrieve_key(t_mini_exc *glob, char *t_key)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(t_key);
	tmp = 0;
	while (glob->envp[i])
	{
		while (glob->envp[i][j] == t_key[j])
			j++;
		if (len == j)
			return (ft_strdup(t_key));
		else
			j = 0;
		i++;
	}
	return (NULL);
}

int		check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if (str[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}