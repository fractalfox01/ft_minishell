/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:56:10 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/03 15:36:39 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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

/*
** Only interaction with global environ variable: copies over to char * array
*/

char	**copy_environ()
{
	int		i;
	char	**envp;

	i = 0;
	envp = NULL;
	while (environ[i])
		i++;
	envp = ft_2d_tab(i);
	i = 0;
	if (envp)
	{
		while (environ[i])
		{
			envp[i] = environ[i];
			i++;
		}
		return (envp);
	}
	ft_putstr_fd("Failed to clone environ\n", 2);
	return (NULL);
}