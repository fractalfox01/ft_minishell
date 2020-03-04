/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 10:47:56 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/04 14:49:36 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	*back_one(t_mini_exc *glob)
{
	int		i;
	int		j;
	char	*tmp;
	char	*pwd;

	i = 0;
	j = 0;
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
					i++;
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

// int		helper_check(int *f1, int *f2, char *hstack)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (hstack[i] != '\0')
// 	{
// 		if ((i % 3) == 0 && i >= 2)
// 		{
// 			if (hstack[i - 2] == '.' && hstack[i - 1] == '.' && hstack[i - 0] == '/')
// 			{
// 				f1[0] = (i - 2);
// 				f2[0] = i;
// 				len -= 3;
// 			}
// 			else
// 				len++;
// 		}
// 		else
// 			len++;
// 		i++;
// 	}
// }

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

void	mini_changedir(t_mini_exc *glob, t_plst *node)
{
	char	cwd[1024];
	char	*pwd;
	// char	*pwd;
	char	*tmp;
	char	*tmp2;
	char	*new_pwd;
	int		i;

	i = 0;
	pwd = NULL;
	tmp = NULL;
	tmp2 = NULL;
	new_pwd = NULL;
	ft_memset(cwd, 0, 1024);
	getcwd(cwd, 1024);
	while (node->argv[i])
		i++;
	if (i > 2)
		return (ft_putstr("builtin cd: too many arguments\n"));
	if (i == 1)
		return ;
	if ((ft_strcmp(node->argv[1], ".") == 0) || (ft_strcmp(node->argv[1], "..") == 0))
	{
		if (ft_strcmp(node->argv[1], "..") == 0)
		{
			pwd = back_one(glob);
			if (chdir(pwd) == 0)
			{
				change_pwd(glob, pwd);
				ft_strdel(&pwd);
				ft_bzero(cwd, 1024);
			}
		}
		return ;
	}
	ft_bzero(cwd, 1024);
	pwd = get_key(glob, "PWD=");
	i = 0;
	while (node->argv[1][i] != '\0')
		i++;
	while ((new_pwd = ft_removestr(node->argv[1], "../")))
	{
		ft_strdel(&node->argv[1]);
		node->argv[1] = ft_strdup(new_pwd);
		tmp = chomp_last(pwd);
		if (tmp)
		{
			ft_strdel(&pwd);
			pwd = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else
			pwd = ft_strdup("/");
		ft_strdel(&new_pwd);
	}
	if (!(new_pwd))
	{
		if (node->argv[1])
		{
			i = ft_strlen(pwd);
			if (node->argv[1][0] == '/' || pwd[(i - 1)] == '/')
			{
				if (node->argv[1][0] == '/')
					tmp = ft_strjoin(pwd, &(node->argv[1][1]));
				else
					tmp = ft_strjoin(pwd, node->argv[1]);
				ft_strdel(&pwd);
				pwd = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
			else
			{
				tmp = ft_strjoin(pwd, "/");
				tmp2 = ft_strjoin(tmp, node->argv[1]);
				ft_strdel(&pwd);
				pwd = ft_strdup(tmp2);
				ft_strdel(&tmp);
				ft_strdel(&tmp2);
			}
		}
	}
	if (chdir(pwd) == 0)
	{
		change_pwd(glob, pwd);
		// ft_strdel(&tmp);
		ft_strdel(&pwd);
	}
}

void	mini_print_env(t_mini_exc *glob, t_plst *node)
{
	int	i;

	i = 0;
	printf("mini env:\n");
	while (node->argv[i])
		i++;
	if (i > 1)
		return ;
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

void	mini_set_env(t_mini_exc *glob, t_plst *node)
{
	int		i;
	int		j;
	int		k;
	int		p;
	int		m;
	char	*tmp;
	char	*t;
	char	**remainder;

	remainder = NULL;
	i = 0;
	j = 0;
	k = 0;
	p = 0;
	m = 0;
	t = NULL;
	tmp = NULL;
	while (node->argv[i])
		i++;
	if (i == 3)
	{
		while (glob->envp[j])
		{
			t = mini_get_env(glob->envp[j]);
			if ((t && ft_strcmp(node->argv[1], t) == 0))
			{
				remainder = copy_remainder(glob, j);
				ft_strdel(&t);
				printf("setting: %s to %s\n", node->argv[1], node->argv[2]);
				while (glob->envp[j][k] != '\0' && glob->envp[j][k] != '=')
					k++;
				printf("before: %s\n", glob->envp[j]);
				while (glob->envp[j][k] != '\0')
					glob->envp[j][k++] = '\0';
				printf("after: %s\n", glob->envp[j]);
				tmp = ft_strjoin(node->argv[1], "=");
				t = ft_strjoin(tmp, node->argv[2]);
				printf("t is %s\n", t);
				ft_memcpy(glob->envp[j], t, ft_strlen(t));
				ft_strdel(&tmp);
				ft_strdel(&t);
				j++;
				k = 0;
				break ;
			}
			ft_strdel(&t);
			j++;
		}
		while (glob->envp[j])
		{
			while (glob->envp[j][k] != '\0')
				k++;
			k = 0;
			while (remainder[m][p] != '\0')
				glob->envp[j][k++] = remainder[m][p++];
			j++;
			k = 0;
			m++;
			p = 0;
		}
	}
	else if (i == 2)
		printf("clearing %s, if found\n", node->argv[1]);
	else if (i == 1)
		mini_print_env(glob, node);
	else
		ft_putstr_fd("setenv: no\n", 2);
	
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
		mini_print_env(glob, node);
	if (ft_strcmp(node->path, "setenv") == 0)
		mini_set_env(glob, node);
	if (ft_strcmp(node->path, "echo") == 0)
	{

	}
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
