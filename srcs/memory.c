/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:07:56 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/05 17:56:58 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc				*find_available_alloc(char type, size_t size)
{
	t_map			*map;
	t_alloc			*alloc;
	t_alloc			*new;

	map = g_map;
	while (map)
	{
		if (map->map_type == type)
		{
			alloc = (t_alloc*)((char*)map + sizeof(t_map));
			while ((char*)alloc < (char*)map + map->map_size)
			{
				if (alloc->available && alloc->size >= size + sizeof(t_alloc))
				{
					new = (t_alloc*)((char*)alloc + sizeof(t_alloc) + size);
					new->available = 1;
					new->size = alloc->size - size - sizeof(t_alloc);
					alloc->available = 0;
					alloc->size = size;
					return (alloc);
				}
				alloc = (t_alloc*)((char*)alloc + alloc->size +
						sizeof(t_alloc));
			}			
		}
		map = map->next;
	}
	return (0);
}

static void			append_map(t_map *map)
{
	t_map			*tmp;

	if (!g_map)
	{
		map->next = 0;
		g_map = map;
		return ;
	}
	if (g_map > map)
	{
		map->next = g_map;
		g_map = map;
		return ;
	}
	tmp = g_map;
	while (tmp->next && tmp->next < map)
		tmp = tmp->next;
	map->next = tmp->next;
	tmp->next = map;
}

t_alloc				*create_new_map(char type, size_t size)
{
	t_map			*map;
	t_alloc			*alloc;
	size_t			map_size;

	map_size = sizeof(t_map);
	map_size += type == LARGE ? size :
		ALLOC_SLOTS * (sizeof(t_alloc) + get_type_size(type));
	if (map_size % PAGE_SIZE)
		map_size += PAGE_SIZE - map_size % PAGE_SIZE;
	if ((map = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (0);
	map->map_type = type;
	map->map_size = map_size;
	append_map(map);
	if (type == LARGE)
		return ((t_alloc*)map);
	alloc = (t_alloc*)((char*)map + sizeof(t_map));
	alloc->available = 1;
	alloc->size = map_size - sizeof(t_alloc) - sizeof(t_map);
	return (find_available_alloc(type, size));
}
