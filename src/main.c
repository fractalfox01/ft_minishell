/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:04:23 by tvandivi          #+#    #+#             */
/*   Updated: 2020/03/03 12:10:43 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	main(void)
{
	t_mini_exc	glob;

	init_mini_glob(&glob);
	start_minishell(&glob);
	return (0);
}