/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:07:52 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/03 12:23:48 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	mini_get_index(int *i, int *stop, int *start, char *cmd)
{
	stop[0] = start[0];
	while (cmd[stop[0]] != '\0')
	{
		if (cmd[stop[0]] != ' ')
			stop[0]++;
		else
			break ;
	}
	i[0] = ((stop[0] - start[0]));
	if (i[0] < 0)
		i[0] *= -1;
	i[0]++;
}

static char *mini_build_tmp(char *cmd, int *i, int *start, int *stop)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnew(i[0]);
	i[0] = 0;
	while (start[0] < stop[0])
		tmp[i[0]++] = cmd[start[0]++];
	if (i[0] > 0)
		tmp[i[0]] = '\0';
	return (tmp);
}

char	*cfds_helper(char *cmd)
{
	int		start;
	int		stop;
	int		i;

	start = 0;
	stop = 0;
	i = 0;
	while (cmd[start] != '\0' && cmd[start] != '$')
		start++;
	if (cmd[start] == '$')
		start++;
	else
		return (NULL);
	mini_get_index(&i, &stop, &start, cmd);
	return (mini_build_tmp(cmd, &i, &start, &stop));
}

char	*compare_environ(t_mini_exc *glob, char *tmp)
{
	int		start;
	char	*ptr;
	char	*exp;

	start = 0;
	ptr = NULL;
	exp = NULL;
	while (glob->envp[start])
	{
		if (ft_strcmp(tmp, (ptr = grab_key(glob->envp[start]))) == 0)
		{
			exp = grab_value(glob->envp[start]);
			ft_strdel(&ptr);
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
	i[0]++;
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
	i = -1;
	j = 0;
	while (cmd[j] != '\0' && cmd[j] != '$')
		j++;
	tmp2 = ft_strnew((j + 1));
	while (i++ < (j - 1))
		tmp2[i] = cmd[i];
	tmp2[i] = '\0';
	i = 0;
	j++;
	if ((ptr = ft_strrchr(command[0], '$')))
	{
		i = find_var_index(j, cmd);
		while (cmd[i] != ' ' && cmd[i] != '\0')
			i++;
		tmp = ft_strdup(&cmd[i]);
		ft_strdel(command);
		command[0] = ft_strjoin(tmp2, tmp);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
}

void	check_for_dollar_sign(t_mini_exc *glob, char **command)
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
		exp = compare_environ(glob, tmp);
		ft_strdel(&tmp);
		if (exp)
			expresion_found(cmd, exp, command);
		else
			bad_expression(cmd, command);
		ptr = NULL;
	}
}