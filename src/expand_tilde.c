/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:15:04 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/05 11:40:47 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		check_for(char *str, char *checkfor)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(checkfor);
	if (str && checkfor)
	{
		while (((str[i] != '\0') && (str[i] == checkfor[i])) && (i < len))
			i++;
		if (i == len)
			return (1);
	}
	return (0);
}

int		is_home(char *str)
{
	return (check_for(str, "HOME="));
}

int		is_pwd(char *str, char *key)
{
	return (check_for(str, key));
}

char	*get_home(t_mini_exc *glob)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	tmp = NULL;
	home = NULL;
	while (glob->envp[i])
	{
		if (is_home(glob->envp[i]))
		{
			tmp = ft_strdup(glob->envp[i]);
			home = ft_strnew((ft_strlen(tmp) - 5));
			ft_strcat(home, &tmp[5]);
			ft_strdel(&tmp);
			break ;
		}
		i++;
	}
	return (home);
}

char	*get_pwd(t_mini_exc *glob)
{
	int		i;
	int		j;
	char	*home;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	home = NULL;
	while (glob->envp[i])
	{
		if (is_pwd(glob->envp[i], "PWD="))
		{
			tmp = ft_strdup(glob->envp[i]);
			while (glob->envp[i][j] != '=')
				j++;
			if (glob->envp[i][j] == '=')
				j++;
			home = ft_strnew((ft_strlen(tmp) - j));
			ft_strcat(home, &tmp[j]);
			ft_strdel(&tmp);
			break ;
		}
		i++;
	}
	return (home);
}

char	*get_key(t_mini_exc *glob, char *key)
{
	int		i;
	int		j;
	char	*ptr;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	ptr = NULL;
	while (glob->envp[i])
	{
		if (is_pwd(glob->envp[i], key))
		{
			tmp = ft_strdup(glob->envp[i]);
			while (glob->envp[i][j] != '=')
				j++;
			if (glob->envp[i][j] == '=')
				j++;
			ptr = ft_strnew((ft_strlen(tmp) - j));
			ft_strcat(ptr, &tmp[j]);
			ft_strdel(&tmp);
			break ;
		}
		i++;
	}
	return (ptr);
}

char	*create_str(char **line, int len)
{
	char	*tmp;
	int	i;
	int	j;
	
	tmp = NULL;
	i = 0;
	j = 0;
	while (line[0][i] != '\0')
	{
		if (line[0][i] == '~')
			j += len;
		else
			j++;
		i++;
	}
	tmp = ft_strnew((j + 1));
	return (tmp);
}

void	build_new(char **line, int len, char *tmp, char *home)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (line[0][i] != '\0')
	{
		if (line[0][i] != '~')
		{
			tmp[(i + j)] = line[0][i];
			i++;
		}
		else
		{
			ft_strncpy(&tmp[(i + j)], home, len);
			i++;
			j += (len - 1);
		}
	}
}

void	check_for_tilde(t_mini_exc *glob, char **line)
{
	char	*h;
	char	*tmp;
	int		len;
	char	*home;

	h = NULL;
	home = get_key(glob, "HOME=");
	len = ft_strlen(home);
	tmp = NULL;
	while ((h = ft_strrchr(line[0], '~')))
	{
		tmp = create_str(line, len);
		build_new(line, len, tmp, home);
		ft_strdel(&line[0]);
		line[0] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}