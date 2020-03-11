/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 10:47:56 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/05 20:36:19 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	*back_one(t_mini_exc *glob)
{
	int		i;
	int		j;
	int		c;
	char	*tmp;
	char	*pwd;

	i = 0;
	j = 0;
	c = 0;
	tmp = NULL;
	while (glob->envp[i])
	{
		while (glob->envp[i][j] != '\0' && j < 4)
			j++;
		if (j == 4)
		{
			if (((glob->envp[i][0] == 'P') && glob->envp[i][1] == 'W') && (glob->envp[i][2] == 'D' && glob->envp[i][3] == '='))
			{
				tmp = ft_strdup(&glob->envp[i][4]);
				i = 0;
				while (tmp[i] != '\0')
				{
					if (tmp[i] == '/')
						c++;
					i++;
				}
				if (c == 1)
				{
					pwd = ft_strdup("/");
					ft_strdel(&tmp);
					return (pwd);
				}
				while (tmp[i] != '/' && i > 0)
					i--;
				pwd = ft_strnew((i + 1));
				pwd = ft_strncpy(pwd, tmp, i);
				ft_strdel(&tmp);
				return (pwd);
			}
		}
		j = 0;
		i++;
	}
	return (NULL);
}

void	change_pwd(t_mini_exc *glob, char *pwd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (glob->envp[i])
	{
		// printf("checking: %s\n", environ[i]);
		while (glob->envp[i][j] != '\0' && j < 4)
			j++;
		if (j == 4)
		{
			if ((((glob->envp[i][0] == 'P') && glob->envp[i][1] == 'W')) && ((glob->envp[i][2] == 'D' && glob->envp[i][3] == '=')))
			{
				glob->envp[i] = ft_strjoin("PWD=", pwd);
				return ;
			}
		}
		j = 0;
		i++;
	}
}

void	change_key(t_mini_exc *glob, char *pwd, char *key)
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


char	*mini_get_env(char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	tmp = ft_strnew((i + 1));
	if (i)
	{
		i = 0;
		while (env[i] != '=' && env[i] != '\0')
		{
			tmp[i] = env[i];
			i++;
		}
		tmp[i] = '\0';
	}
	return (tmp);
}

char	*ft_removestr(char *hstack, char *needle)
{
	char	*ptr;
	char	*t;
	char	*t2;
	int		i;
	int		start;
	int		stop;
	int		n_len;

	i = 0;
	start = 0;
	stop = 0;
	n_len = ft_strlen(needle);
	t = NULL;
	t2 = NULL;
	ptr = NULL;
	if (hstack)
	{
		while (hstack[i] != '\0')
		{
			if (hstack[i] == needle[start])
			{
				i++;
				start++;
				if (start == n_len)
				{
					stop = start;
					break;
				}
			}
			else
			{
				if (start)
					start = 0;
				i++;
			}
		}
		if (start)
		{
			start -= n_len;
			t = ft_strnew(start);
			t = ft_strncpy(t, hstack, start);
			i = ft_strlen(hstack);
			t2 = ft_strdup(&hstack[stop]);
			ptr = ft_strjoin(t, t2);
			ft_strdel(&t);
			ft_strdel(&t2);
			return (ptr);
		}
	}
	return (NULL);
}

char	*chomp_last(char *pwd)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (pwd[i] != '\0')
		i++;
	while (i > 0 && pwd[i] != '/')
		i--;
	if (i)
	{
		ret = ft_strnew(i);
		ret = ft_strncpy(ret, pwd, i);
	}
	return (ret);
}

int		ft_2dlen(char **tab)
{
	int	ret;

	ret = 0;
	while (tab[ret])
		ret++;
	return (ret);
}

int		validate_cd_command(int size)
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

int		check_cd_basic(t_mini_exc *glob, char *path)
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

void	mini_changedir(t_mini_exc *glob, t_plst *node)
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
	}
	if (node->argv[1])
		path = ft_strdup(node->argv[1]);
	else
		path = ft_strdup(".");
}

void	mini_print_env(t_mini_exc *glob)
{
	int	i;

	i = 0;
	while (glob->envp[i])
	{
		ft_putstr(glob->envp[i++]);
		ft_putchar('\n');
	}
}

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
	{
		printf("pretending to add new key and value...\n");
		// append_key();
	}
	ft_strdel(&t_key);
}

void	mini_set_env(t_mini_exc *glob, t_plst *node)
{
	int		i;
	
	i = 0;
	
	while (node->argv[i])
		i++;
	if (i == 3)
		mini_update_env(glob, node->argv[1], node->argv[2]);
		// printf("sets %s to %s\n", node->argv[1], node->argv[2]);
	else if (i == 2)
		printf("clearing %s, if found\n", node->argv[1]);
	else if (i == 1)
		mini_print_env(glob);
	else
		ft_putstr_fd("setenv: no\n", 2);
	
}

void	mini_echo(t_mini_exc *glob, t_plst *node)
{
	int	i;

	i = 1;
	while (node->argv[i] && glob)
	{
		ft_putstr(node->argv[i++]);
		if (node->argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	run_builtin(t_mini_exc *glob, t_plst *node)
{
	if (glob)
	{
		
	}
	if (ft_strcmp(node->path, "exit") == 0)
		exit (0);
	if (ft_strcmp(node->path, "cd") == 0)
		mini_changedir(glob, node);
	if (ft_strcmp(node->path, "env") == 0)
		mini_print_env(glob);
	if (ft_strcmp(node->path, "setenv") == 0)
		mini_set_env(glob, node);
	if (ft_strcmp(node->path, "echo") == 0)
		mini_echo(glob, node);
	if (ft_strcmp(node->path, "unsetenv") == 0)
	{

	}
	if (ft_strcmp(node->path, "clear") == 0)
	{

	}
	if (ft_strcmp(node->path, "history") == 0)
	{

	}
}
