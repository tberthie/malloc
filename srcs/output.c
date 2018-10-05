/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:30:51 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/05 18:11:12 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

static void		print_hex(unsigned long addr)
{
	// reverse output
	write(1, "0x", 2);
	while (addr >= 16)
	{
		write(1, &HEX[addr % 16], 1);
		addr /= 16;
	}
	write(1, &HEX[addr % 16], 1);
}

static void		print_map(t_map *map)
{
	if (map->map_type == TINY)
		write(1, "TINY : ", 7);
	else if (map->map_type == SMALL)
		write(1, "SMALL : ", 8);
	else if (map->map_type == LARGE)
		write(1, "LARGE : ", 8);
	print_hex(map);
	write(1, "\n", 1);
}

static void		print_alloc(t_alloc *alloc)
{
	// output for large ?
	print_hex((char*)alloc + sizeof(t_alloc));
	write(1, " - ", 3);
	print_hex((char*)alloc + sizeof(t_alloc) + alloc->size);
	write(1, "\n", 1);
}

void			show_alloc_mem()
{
	t_map		*map;
	t_alloc		*alloc;

	map = g_map;
	while (map)
	{
		print_map((char*)map);
		if (map->map_type != LARGE)
		{
			alloc = (t_alloc*)((char*)map + sizeof(t_map));
			while ((char*)alloc < (char*)map + map->map_size)
			{
				if (!alloc->available)
					print_alloc(alloc);
				alloc = (t_alloc*)((char*)alloc + sizeof(t_alloc)
						+ alloc->size);
			}
		}
		// else
		// { }
		map = map->next;
	}
}
