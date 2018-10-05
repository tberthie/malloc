/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:30:51 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/05 17:46:05 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

void			show_alloc_mem()
{
	t_map		*map;
	t_alloc		*alloc;

	map = g_map;
	while (map)
	{
		printf("Map [%zu]\n", map->map_size);
		if (map->map_type != LARGE)
		{
			alloc = (char*)map + sizeof(t_map);
			while (alloc < (char*)map + map->map_size)
			{
				printf("\tAlloc [%d][%x]\n", alloc->available, alloc);
				alloc = (char*)alloc + alloc->size + sizeof(t_alloc);
			}
		}
		map = map->next;
	}
}
