/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:22:08 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/27 09:51:30 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	get_args_init(int *i, int *j, int *end, int *count)
{
	i[0] = 0;
	j[0] = 0;
	end[0] = 0;
	count[0] = 0;
}

static char *ft_strndup(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] != '\0' && str[i] != ' ')
	{
		i++;
	}
	ret = ft_strnew(i);
	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

void	init_var(int *i, int *end, int *count, char *str)
{
	while ((str[i[0]] != '\0') && (str[i[0]] == ' '))
		i[0]++;
	while (str[end[0]] != '\0')
		end[0]++;
	end[0]--;
	while ((end[0] >= 0) && (str[end[0]] == ' '))
		end[0]--;
	if (str[end[0] + 1] == ' ' || str[end[0] + 1] == '\0')
		end[0]++;
	while (str[i[0]] != '\0')
	{
		if ((str[i[0]] == ' ') && (i[0] < end[0]))
			count[0]++;
		i[0]++;
	}
	count[0]++;
}

static char	**get_args(char *str)
{
	int		i;
	int		j;
	int		end;
	int		count;
	char	**ret;

	j = 0;
	get_args_init(&i, &j, &end, &count);
	ret = NULL;
	init_var(&i, &end, &count, str);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	while (j < count)
	{
		ret[j++] = ft_strndup(str);
		while (*str != '\0' && (*str != ' '))
			str++;
		str++;
	}
	ret[j] = NULL;
	return (ret);
}

static char **get_env()
{
	char **ep;
	int i;

	ep = NULL;
	i = 0;
	while (environ[i])
		i++;
	ep = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		ep[i] = ft_strdup(environ[i]);
		i++;
	}
	ep[i] = NULL;
	return (ep);
}

char	*grab_key(char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;	
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		i++;
	}
	if (str[i] == '=')
	{
		tmp = (char *)malloc(sizeof(char) * (i + 1));
	}
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

	
/*
** returns str if no '=' found.
** key=value grabs value and returns
*/

char	*grab_value(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	ret = NULL;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		i++;
		ret = ft_strdup(&str[i]);
	}
	else
		return (str);
	return (ret);
}

t_plst	*init_node()
{
	t_plst	*node;

	node = (t_plst *)malloc(sizeof(t_plst) * 1);
	node->argv = NULL;
	node->envp = NULL;
	node->path = NULL;
	node->ampersand = 0;
	node->next = NULL;
	return (node);
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

char	*ft_sentencetrim(char *str)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*tmp;
	char	*ret;
	int		c_btw;
	int		ampersand;
	int		semicolon;

	i = 0;
	j = 0;
	k = 0;
	ampersand = 0;
	semicolon = 0;
	c_btw = 0;
	tmp = NULL;
	ret = NULL;
	tmp = ft_strtrim(str);
	len = ft_strlen(tmp);
	while (tmp[i] != '\0')
	{
		if (ft_whitespace(tmp[i]) && ft_whitespace(tmp[(i + 1)]))
			len--;
		i++;
	}
	i = 0;
	ret = ft_strnew(len);
	if (ret)
	{
		while (tmp[i] != '\0')
		{
			if (ft_whitespace(tmp[i]) && ((ft_whitespace(tmp[i + 1]) == 0) && (tmp[i + 1] != ';')))
			{
				if ((i > 0) && (tmp[i - 1] != ';'))
				{
					k = i - 1;
					while (k > 0)
					{
						if (tmp[k] == ' ')
							k--;
						else
							break ;
					}
					if (tmp[k] != ';')
						ret[j++] = tmp[i];
					k = 0;
				}
				if (i == 0)
					ret[j++] = tmp[i];
			}
			else if (!(ft_whitespace(tmp[i])))
				ret[j++] = tmp[i];
			i++;
		}
		ret[j] = '\0';
	}
	return (ret);
}

int		check_for_ampersand(char **str)
{
	int 	ret;
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	ret = 0;
	s1 = NULL;
	s2 = NULL;
	while (str[0][i] != '\0')
	{
		if (str[0][i] == '&')
		{
			ret++;
			s1 = ft_strnew(i + 1);
			s1 = ft_strncpy(s1, str[0], i);
			i++;
			s2 = ft_strjoin(s1, &str[0][i]);
			ft_strdel(&s1);
			ft_strdel(str);
			str[0] = ft_strdup(s2);
			ft_strdel(&s2);
			check_for_ampersand(str);
			break ;
		}
		i++;
	}
	return (ret);
}

static int		check_for(char *str, char *checkfor)
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

static int		is_home(char *str)
{
	return (check_for(str, "HOME="));
}

char	*mini_get_home()
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	while (environ[i])
	{
		if (is_home(environ[i]))
		{
			home = ft_strdup(environ[i]);
			break ;
		}
		i++;
	}
	return (home);
}

int		check_if_exacutable(char *path)
{
	int		ret;
	char	*tpath;
	char	*home;
	char	*tmp;

	home = mini_get_home();
	tmp = ft_strjoin((home + 5), "/");
	tpath = ft_strjoin(tmp, path);
	ft_strdel(&home);
	ft_strdel(&tmp);
	ret = 0;
	if (access(path, X_OK) == 0)
	{
		ret = 1;
	}
	ft_strdel(&tpath);
	return (ret);
}

t_plst *new_process(char *command)
{
	t_plst	*node;
	t_plst	*root;
	char	*path;
	char	**av;
	char	**ep;
	char	**tab;
	int		i;
	int		good;
	char	*trimmed;
	char	*c;
	int		k;
	int		n;
	int		amp;

	amp = 0;
	n = 0;
	k = 0;
	good = 0;
	i = 0;
	tab = NULL;
	node = NULL;
	c = NULL;
	trimmed = ft_sentencetrim(command);
	tab = ft_strsplit(trimmed, ';');
	if (trimmed)
		ft_strdel(&trimmed);
	root = NULL;
	if (tab)
	{
		while (tab[i])
		{
			amp = check_for_ampersand(&tab[i]);
			check_for_tilde(&tab[i]);
			check_for_dollar_sign(&tab[i]);
			path = get_path(tab[i]);
			good = expand_path(&path);
			if (good)
			{
				if (av)
					av = NULL;
				av = get_args(tab[i]);
				if (ep)
					ep = NULL;
				ep = get_env();
				if (i == 0)
				{
					node = init_node();
					root = node;
				}
				node->path = ft_strdup(path);
				if (amp)
				{
					node->ampersand = 1;
					amp = 0;
				}
				ft_strdel(&path);
				node->argv = av;
				node->envp = ep;
				c = NULL;
				if (tab[i + 1])
				{
					node->next = init_node();
					node = node->next;
				}
				else
					node->next = NULL;
			}
			else if (check_if_exacutable(path))
			{
				if (av)
					av = NULL;
				av = get_args(tab[i]);
				if (ep)
					ep = NULL;
				ep = get_env();
				if (i == 0)
				{
					node = init_node();
					root = node;
				}
				char *home = mini_get_home();
				char *tmp = ft_strjoin((home + 5), "/");
				node->path = ft_strdup(path);
				ft_strdel(&home);
				ft_strdel(&tmp);
				if (amp)
				{
					node->ampersand = 1;
					amp = 0;
				}
				ft_strdel(&path);
				node->argv = av;
				node->envp = ep;
				c = NULL;
				if (tab[i + 1])
				{
					node->next = init_node();
					node = node->next;
				}
				else
					node->next = NULL;
			}
			else
			{
				ft_putstr_fd("ft_minishell: command not found: ", 2);
				ft_putstr_fd(path, 2);
				ft_putstr_fd("\n", 2);
			}
			i++;
		}		
	}
	return (root);
}

void	free_process(t_plst **process)
{
	int	i;

	i = 0;
	if (process[0])
	{
		if (process[0]->path)
			ft_strdel(&process[0]->path);
		if (process[0]->argv)
		{
			while (process[0]->argv[i])
			{
				ft_strdel(&process[0]->argv[i++]);
			}
			free(process[0]->argv);
			i = 0;
		}
		if (process[0]->envp)
		{
			while (process[0]->envp[i])
				ft_strdel(&process[0]->envp[i++]);
			free(process[0]->envp);
			i = 0;
		}
		free(process[0]);
		process[0] = NULL;
	}
}