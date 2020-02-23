/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvandivi <tvandivi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:49:13 by tvandivi          #+#    #+#             */
/*   Updated: 2020/02/04 17:08:19 by tvandivi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *tab, size_t size)
{
	void	*ptr;

	ptr = ft_memalloc(size);
	if (!tab || ptr)
		return (NULL);
	ptr = ft_memcpy(ptr, tab, sizeof(tab));
	free(tab);
	return (ptr);
}
