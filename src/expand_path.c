/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:33:57 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/23 19:35:18 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	is_path(char *str)
{
	int		i;
	char	test[6] = "PATH=";

	i = 0;
	if (str)
	{
		while ((str[i] == test[i]) && (i < 6))
			i++;
		if (i == 5)
			return (1);
	}
	return (0);
}

static char	*chomp_path(char *str)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (str)
	{
		str += 5;
		path = ft_strdup(str);
	}
	return (path);
}

static char	**obtain_paths(void)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	paths = NULL;
	if (environ[i])
	{
		while (environ[i])
		{
			if (is_path(environ[i]))
			{
				path = chomp_path(environ[i]);
				break ;
			}
			i++;
		}
		paths = ft_strsplit(path, ':');
		ft_strdel(&path);
	}
	return (paths);
}

static char	*get_path(char *str)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (str[len] == ' ')
		len++;
	while (str[len] != '\0' && str[len] != ' ')
		len++;
	char *ret = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0' && str[i] != ' ')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*all_but_first(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	if (str[i] == ' ')
	{
		len = ft_strlen(&str[i]);
		ret = ft_strnew((i + 1));
		ret = ft_strcpy(ret, &str[i]);
		return (ret);
	}
	return (NULL);
}

void	check_dir_for_cmd(char *env_paths, DIR *dr, char *path, char **command)
{
	int				i;
	char			*tmp;
	// char			*tmp2;
	char			*full_path;
	struct dirent	*dent;

	// tmp2 = NULL;
	while ((dent = readdir(dr)))
	{
		if (ft_strcmp(dent->d_name, path) == 0)
		{
			i = 1;
			tmp = ft_strjoin(env_paths, "/");
			full_path = ft_strjoin(tmp, dent->d_name);
			ft_strdel(&tmp);
			// tmp2 = all_but_first(command[0]);
			ft_strdel(&command[0]);
			command[0] = ft_strdup(full_path);
			// ft_strdel(&tmp2);
			ft_strdel(&full_path);
			closedir(dr);
			return ;
		}
	}
	closedir(dr);
	dr = NULL;
}

void	expand_path(char **command)
{
	char			*path;
	char			**env_paths;
	int				i;
	DIR				*dr;
	struct stat		st;

	i = 0;
	dr = NULL;
	path = NULL;
	path = get_path(command[0]);
	env_paths = obtain_paths();
	while (env_paths[i])
	{
		st.st_mode = 0;
		lstat(env_paths[i], &st);
		if (S_ISDIR(st.st_mode) > 0)
		{
			dr = opendir(env_paths[i]);
			if (dr)
				check_dir_for_cmd(env_paths[i], dr, path, command);
		}
		i++;
	}
}