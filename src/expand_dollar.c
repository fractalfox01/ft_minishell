/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:07:52 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/23 10:53:53 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	*cfds_helper(char *cmd)
{
	int		start;
	int		stop;
	int		i;
	char	*tmp;

	start = 0;
	stop = 0;
	i = 0;
	tmp = NULL;
	while (cmd[start] != '\0' && cmd[start] != '$')
		start++;
	if (cmd[start] == '$')
		start++;
	else
		return (NULL);
	stop = start;
	while (cmd[stop] != '\0')
	{
		if (cmd[stop] >= 'A' && cmd[stop] <= 'Z')
			stop++;
		else if (cmd[stop] == '_')
			stop++;
		else if (cmd[stop] >= '0' && cmd[stop] <= '9')
			stop++;
		else
			break ;
	}
	if (stop > start)
	{
		i = ((stop - start) + 1);
		tmp = ft_strnew(i);
		i = 0;
	}
	else
	{
		i = ((start - stop) + 1);
		tmp = ft_strnew(i);
		i = 0;
	}
	while (start < stop)
	{
		tmp[i++] = cmd[start];
		start++;
	}
	tmp[start] = '\0';
	return (tmp);
}

char	*compare_environ(char *tmp)
{
	int		start;
	char	*ptr;
	char	*exp;

	start = 0;
	ptr = NULL;
	exp = NULL;
	while (environ[start])
	{
		if (ft_strcmp(tmp, (ptr = grab_key(environ[start]))) == 0)
		{
			exp = grab_value(environ[start]);
			break ;
		}
		ft_strdel(&ptr);
		start++;
	}
	return (exp);
}

int		find_var_index(int i, char *cmd)
{
	while (cmd[i] != '\0')
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			i++;
		else if (cmd[i] == '_')
			i++;
		else if (cmd[i] >= '0' && cmd[i] <= '9')
			i++;
		else
			break ;
	}
	return (i);
}

void	end_check(int i, char *cmd, char *tmp, char **command)
{
	int		j;
	int		start;
	char	*tmp2;
	
	tmp2 = NULL;
	start = 0;
	j = i;
	while (cmd[j] != '\0')
		j++;
	start = i - j;
	if (start < 0)
		start *= -1;
	tmp2 = ft_strnew((start + 1));
	j = i;
	i = 0;
	while (cmd[j] != '\0')
		tmp2[i++] = cmd[j++];
	tmp2[i] = '\0';
	command[0] = ft_strjoin(tmp, tmp2);
	ft_strdel(&tmp2);
}

char	*copy_before(char *cmd, int *i)
{
	char	*tmp2;

	tmp2 = NULL;
	while (cmd[i[0]] != '$')
		i[0]++;
	tmp2 = ft_strnew((i[0] + 1));
	i[0] = 0;
	while (cmd[i[0]] != '$')
	{
		tmp2[i[0]] = cmd[i[0]];
		i[0]++;
	}
	tmp2[i[0]] = '\0';
	return (tmp2);
}

/*
** join first part to exp then copy all remaining characters, then
** delete and rebuild as command[0], rerun through check_for_dollar_sign
** until no expansion needed.
*/

void	expresion_found(char *cmd, char *exp, char **command)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	tmp2 = copy_before(cmd, &i);
	i++;
	tmp = ft_strjoin(tmp2, exp);
	ft_strdel(&exp);
	ft_strdel(&tmp2);
	i = find_var_index(i , cmd);
	if (cmd[i] != '\0')
	{
		end_check(i, cmd, tmp, command);
		if (tmp)
			ft_strdel(&tmp);
		if (cmd)
			ft_strdel(&cmd);
	}
	else
	{
		ft_strdel(command);
		command[0] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

void	bad_expression(char *cmd, char **command)
{
	int		i;
	int		j;
	char	*ptr;
	char	*tmp2;
	char	*tmp;

	ptr = NULL;
	i = 0;
	j = 0;
	while (cmd[j] != '\0' && cmd[j] != '$')
		j++;
	tmp2 = ft_strnew((j + 1));
	while (i < j)
	{
		tmp2[i] = cmd[i];
		i++;
	}
	tmp2[i] = '\0';
	i = 0;
	j++;
	if ((ptr = ft_strrchr(command[0], '$')))
	{
		i = find_var_index(j, cmd);
		tmp = ft_strdup(&cmd[i]);
		ft_strdel(command);
		command[0] = ft_strjoin(tmp2, tmp);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
}

void	check_for_dollar_sign(char **command)
{
	char	*cmd;
	char	*ptr;
	char	*tmp;
	char	*exp;

	exp = NULL;
	tmp = NULL;
	ptr = NULL;
	cmd = NULL;
	while ((ptr = ft_strrchr(command[0], '$')))
	{
		cmd = command[0];
		tmp = cfds_helper(cmd);
		if (!(tmp))
			return ;
		exp = compare_environ(tmp);
		ft_strdel(&tmp);
		if (exp)
			expresion_found(cmd, exp, command);
		else
			bad_expression(cmd, command);
	}
}