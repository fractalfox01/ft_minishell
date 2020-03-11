/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_set_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:57:58 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 15:07:20 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	append_key_and_value(t_mini_exc *glob, char *key, char *value)
{
	int		i;
	char	*tmp;
	char	**tmp_envp;

	i = 0;
	tmp_envp = NULL;
	if (check_key(key))
		return ;
	while (glob->envp[i])
		i++;
	tmp_envp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (glob->envp[i])
	{
		tmp_envp[i] = ft_strdup(glob->envp[i]);
		ft_strdel(&glob->envp[i]);
		i++;
	}
	free(*glob->envp);
	tmp = ft_strjoin(key, "=");
	tmp_envp[i++] = ft_strjoin(tmp, value);
	ft_strdel(&tmp);
	tmp_envp[i] = NULL;
	glob->envp = tmp_envp;
}

void	mini_update_env(t_mini_exc *glob, char *key, char *valu)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	*t_key;

	i = 0;
	j = 0;
	tmp = NULL;
	t_key = ft_strjoin(key, "=");
	len = ft_strlen(t_key) - 1;
	if ((tmp = retrieve_key(glob, t_key)))
	{
		ft_strdel(&tmp);
		while (glob->envp[i])
		{
			while (glob->envp[i][j] != '\0' && (glob->envp[i][j] != '=' && (j < len)))
				j++;
			if (glob->envp[i][j] == '=')
			{
				if (j == len)
				{
					tmp = ft_strnew(j);
					tmp = ft_strncpy(tmp, glob->envp[i], j);
					if (ft_strcmp(tmp, key) == 0)
					{
						ft_strdel(&tmp);
						ft_strdel(&glob->envp[i]);
						glob->envp[i] = ft_strjoin(t_key, valu);
						break ;
					}
					ft_strdel(&tmp);
				}
			}
			j = 0;
			i++;
		}
	}
	else
		append_key_and_value(glob, key, valu);
	ft_strdel(&t_key);
}

static void	mini_remove_env(t_mini_exc *glob, char *key)
{
	int	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	// while (glob->envp[i])
	// {
	tmp2 = ft_strjoin(key, "=");
	if ((i = check_for_key(glob, key)))
	{
		printf("found at idx [%d]: %s\n", i,  glob->envp[i]);
	}
	else
		ft_putstr("key not found\n");
		// i++;
	// }
}

void	mini_set_env(t_mini_exc *glob, t_plst *node)
{
	int		i;

	i = 0;

	while (node->argv[i])
		i++;
	if (i == 3)
		mini_update_env(glob, node->argv[1], node->argv[2]);
	else if (i == 2)
		mini_remove_env(glob, node->argv[1]);
	else if (i == 1)
		mini_print_env(glob);
	else
		ft_putstr_fd("Ft_minishell: setenv says: no\n", 2);
}
