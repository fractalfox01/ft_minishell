/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:15:04 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/24 11:53:05 by tvandivi         ###   ########.fr       */
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

char	*get_home()
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	tmp = NULL;
	home = NULL;
	while (environ[i])
	{
		if (is_home(environ[i]))
		{
			tmp = ft_strdup(environ[i]);
			home = ft_strnew((ft_strlen(tmp) - 5));
			ft_strcat(home, &tmp[5]);
			ft_strdel(&tmp);
			break ;
		}
		i++;
	}
	return (home);
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

void	check_for_tilde(char **line)
{
	char	*h;
	char	*tmp;
	int		len;
	char	*home;

	h = NULL;
	home = get_home();
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