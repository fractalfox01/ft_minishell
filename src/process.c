/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:22:08 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/23 17:50:14 by tvandivi         ###   ########.fr       */
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
		ret[j] = ft_strndup(str);
		while (*str != '\0' && (*str != ' '))
			str++;
		str++;
		j++;
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

t_plst *new_process(char *command)
{
	t_plst	*node;
	char	*path;
	char	**av;
	char	**ep;
	
	node = init_node();
	check_for_tilde(&command);
	check_for_dollar_sign(&command);
	path = get_path(command);
	expand_path(&path);
	av = get_args(command);
	ep = get_env();
	node->path = ft_strdup(path);
	ft_strdel(&path);
	node->argv = av;
	node->envp = ep;
	node->next = NULL;
	return (node);
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