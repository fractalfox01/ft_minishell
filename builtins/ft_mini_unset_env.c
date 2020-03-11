/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_unset_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:54:14 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/09 14:54:25 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	mini_unset_env(t_mini_exc *glob, t_plst *node)
{
	if (glob && node)
		mini_set_env(glob, node);
}
