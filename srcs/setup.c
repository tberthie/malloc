/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 13:50:17 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 14:47:28 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char		setup(void)
{
	if (!(g_alloc.tiny = (void**)map_memory(sizeof(void*))) ||
	!(g_alloc.small = (void**)map_memory(sizeof(void*))) ||
	!(g_alloc.large = (void**)map_memory(sizeof(void*))))
		return (0);
	*g_alloc.tiny = 0;
	*g_alloc.small = 0;
	*g_alloc.large = 0;
	return ((g_init = 1));
}
