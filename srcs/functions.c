/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:04:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 15:40:12 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

t_block			*g_alloc = 0;

void			*malloc(size_t size)
{
	char			type;

	type = (size > TINY_MAX) + (size > SMALL_MAX);
	if (size <= 0)
		return (NULL);
	return (get_memory(type, size));
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*block;
	t_zone		*zone;

	block = g_alloc;
	while (ptr && block)
	{
		if ((zone = find_ptr(block, ptr)))
		{
			if ((size > TINY_MAX) + (size > SMALL_MAX) != block->type || (size >
			zone->len && (zone->next || block->space < size - zone->len)))
				return (zcpy(zone, size));
			zone->len = size;
			block->space -= size - zone->len;
			return (ptr);
		}
		block = block->next;
	}
	return (NULL);
}

void			free(void *ptr)
{
	t_block		*block;
	t_zone		*zone;

	block = g_alloc;
	while (ptr && block)
	{
		if ((zone = find_ptr(block, ptr)))
		{
			zone->free = 1;
			break ;
		}
		block = block->next;
	}
	if (!ptr || !block)
		return ;
	zone = block->zones;
	while (zone)
	{
		if (!zone->free)
			return ;
		zone = zone->next;
	}
	if (block == g_alloc)
		g_alloc = block->next;
	munmap(block->map - sizeof(t_block), block->space + sizeof(t_block));
}

void			show_alloc_mem(void)
{
	t_block		*block;
	size_t		total;

	total = 0;
	block = g_alloc;
	while (block)
	{
		if (block->type == TINY)
			write(1, "TINY : ", 7);
		else if (block->type == SMALL)
			write(1, "SMALL : ", 8);
		else
			write(1, "LARGE : ", 8);
		print_exha((size_t)block->map);
		write(1, "\n", 1);
		total += print_zones(block);
		block = block->next;
	}
	write(1, "Total : ", 8);
	print_size(total);
	write(1, " octets\n", 9);
}
