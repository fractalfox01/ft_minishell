/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:33:57 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/03 12:24:16 by tvandivi         ###   ########.fr       */
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

static char	**obtain_paths(t_mini_exc *glob)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	paths = NULL;
	if (glob->envp[i])
	{
		while (glob->envp[i])
		{
			if (is_path(glob->envp[i]))
			{
				path = chomp_path(glob->envp[i]);
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
	int	i;
	int	len;
	char	*ret;

	i = 0;
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

int		check_dir_for_cmd(char *env_paths, DIR *dr, char *path, char **command)
{
	char		*tmp;
	char		*full_path;
	struct dirent	*dent;
	int		i;
	
	i = 0;
	while ((dent = readdir(dr)))
	{
		if (ft_strcmp(dent->d_name, path) == 0)
		{
			i = 1;
			tmp = ft_strjoin(env_paths, "/");
			full_path = ft_strjoin(tmp, dent->d_name);
			ft_strdel(&tmp);
			ft_strdel(&command[0]);
			command[0] = ft_strdup(full_path);
			ft_strdel(&full_path);
			closedir(dr);
			return (1);
		}
	}
	closedir(dr);
	dr = NULL;
	return (0);
}

static int		check_if_builtin(char *path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i] != '\0' && path[i] != ' ')
		i++;
	tmp = ft_strnew(i);
	i = 0;
	while (path[i] != '\0' && path[i] != ' ')
	{
		tmp[i] = path[i];
		i++;
	}
	tmp[i] = '\0';
	if (ft_strcmp(tmp, "exit") == 0)
		return (1);
	if (ft_strcmp(tmp, "cd") == 0)
		return (1);
	if (ft_strcmp(tmp, "env") == 0)
		return (1);
	if (ft_strcmp(tmp, "setenv") == 0)
		return (1);
	if (ft_strcmp(tmp, "echo") == 0)
		return (1);
	if (ft_strcmp(tmp, "unsetenv") == 0)
		return (1);
	return (0);
}

int		expand_path(t_mini_exc *glob, char **command)
{
	char			*path;
	char			**env_paths;
	int				i;
	DIR				*dr;
	struct stat		st;
	int				ret;

	ret = 0;
	i = 0;
	dr = NULL;
	path = NULL;
	if (check_if_builtin(command[0]) == 0)
	{
		path = get_path(command[0]);
		env_paths = obtain_paths(glob);
		while (env_paths[i])
		{
			st.st_mode = 0;
			lstat(env_paths[i], &st);
			if (S_ISDIR(st.st_mode) > 0)
			{
				dr = opendir(env_paths[i]);
				if (dr)
				{
					ret = check_dir_for_cmd(env_paths[i], dr, path, command);
					if (ret)
						break ;
				}
			}
			i++;
		}
	}
	return (ret);
}
