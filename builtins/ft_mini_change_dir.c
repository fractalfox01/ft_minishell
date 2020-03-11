/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_change_dir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:10:27 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/11 11:40:11 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int			validate_cd_command(int size)
{
	int	ret;

	ret = 0;
	if (size > 2)
	{
		ft_putstr_fd("builtin cd: too many arguments\n", 2);
		ret = 1;
	}
	else if (size == 1)
		ret = 2;
	return (ret);
}

void		change_key(t_mini_exc *glob, char *pwd, char *key)
{
	int	i;
	int	j;
	int	n;
	int	len;
	int	count;

	i = 0;
	j = 0;
	n = 0;
	len = 0;
	count = 0;
	while (key[len] != '\0')
		len++;
	while (glob->envp[i])
	{
		while (glob->envp[i][j] != '\0' && j < len)
			j++;
		if (j == len)
		{
			while (key[n] != '\0')
			{
				if (glob->envp[i][n] == key[n])
					count++;
				else
					break ;
				n++;
			}
			if (count == len)
			{
				free(glob->envp[i]);
				glob->envp[i] = NULL;
				glob->envp[i] = ft_strjoin(key, pwd);
				return ;
			}
			count = 0;
		}
		n = 0;
		j = 0;
		i++;
	}
}

static int	check_cd_basic(t_mini_exc *glob, char *path)
{
	char	*pwd;
	int		i;
	int		count;
	char	cwd[1024];
	char	old[1024];

	pwd = NULL;
	i = 0;
	count = 0;
	ft_memset(cwd, '\0', 1024);
	ft_memset(old, '\0', 1024);
	if ((ft_strcmp(path, ".") == 0) || (ft_strcmp(path, "..") == 0))
	{
		if (ft_strcmp(path, "..") == 0)
		{
			getcwd(old, 1024);
			while (old[i] != '\0')
			{
				if (old[i] == '/')
					count++;
				i++;
			}
			if (count <= 1)
				pwd = ft_strdup("/");
			else
			{
				while ((i > 0) && (old[i] != '/'))
					i--;
				if (i != 0 && old[i] == '/')
				{
					pwd = ft_strnew(i);
					pwd = ft_strncpy(pwd, old, i);
				}
				else if (i == 0 || old[i] == '/')
					pwd = ft_strdup("/");
			}
			if (chdir(pwd) == 0)
			{
				change_key(glob, old, "OLDPWD=");
				getcwd(cwd, 1024);
				change_key(glob, cwd, "PWD=");
				ft_strdel(&path);
				ft_strdel(&pwd);
			}
		}
		else
		{
			getcwd(old, 1024);
			change_key(glob, old, "OLDPWD=");
			getcwd(cwd, 1024);
			change_key(glob, cwd, "PWD=");
			ft_strdel(&path);
		}
		return (1);
	}
	return (0);
}

void		mini_changedir(t_mini_exc *glob, t_plst *node)
{
	char	cwd[1024];
	char	old[1024];
	char	*path;
	char	*newpwd;
	int		i;

	i = ft_2dlen(node->argv);
	newpwd = NULL;
	path = NULL;
	ft_memset(cwd, '\0', 1024);
	ft_memset(old, '\0', 1024);
	if (validate_cd_command(i) == 0 && node->argv[1])
	{
		path = ft_strdup(node->argv[1]);
		if (check_cd_basic(glob, path))
			return ;
		getcwd(old, 1024);
		if (chdir(path) == 0)
		{
			change_key(glob, old, "OLDPWD=");
			getcwd(cwd, 1024);
			change_key(glob, cwd, "PWD=");
			ft_strdel(&path);
		}
		else
		{
			ft_putstr_fd("Ft_minishell: no such file or directory: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\n", 2);
		}
	}
}
