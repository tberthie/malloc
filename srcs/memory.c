/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 13:05:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 19:34:11 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

static void		*get_map(size_t size)
{
	struct rlimit	limit;
	void			*ptr;

	getrlimit(RLIMIT_MEMLOCK, &limit);
	if (size > limit.rlim_cur)
		write(2, "Size exceeds allocation limit\n", 31);
	else if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE |
	MAP_ANON, -1, 0)) == MAP_FAILED)
		write(2, "Failed to map memory\n", 28);
	else
		return (ptr);
	return (NULL);
}

static t_block	*find_block(char type, size_t size)
{
	t_block		*block;

	block = g_alloc;
	while (block)
	{
		if (block->type == type && block->space >= size + sizeof(t_zone))
			return (block);
		block = block->next;
	}
	return (NULL);
}

static t_block	*create_block(char type, size_t size)
{
	t_block		*block;
	t_block		*blocks;
	void		*map;

	if (type == LARGE)
		size += sizeof(t_block);
	else
		size = sizeof(t_block) + 100 * (sizeof(t_zone) + (type == SMALL ?
		SMALL_MAX : TINY_MAX));
	size += size % PAGE;
	if (!(map = get_map(size)))
		return (NULL);
	blocks = g_alloc;
	while (blocks && blocks->next)
		blocks = blocks->next;
	block = (t_block*)map;
	block->map = map + sizeof(t_block);
	block->space = size - sizeof(t_block);
	block->type = type;
	block->zones = 0;
	block->next = 0;
	if (blocks)
		blocks->next = block;
	g_alloc = g_alloc ? g_alloc : block;
	return (block);
}

static void		*allocate_zone(t_block *block, size_t size)
{
	void	*ptr;
	t_zone	*zone;
	t_zone	*new;

	ptr = block->map;
	if (!(zone = block->zones))
	{
		new = (t_zone*)block->map;
		new->ptr = block->map + sizeof(t_zone);
		block->zones = new;
	}
	else
	{
		while (zone->next)
			zone = zone->next;
		new = (t_zone*)(zone->ptr + zone->len);
		new->ptr = new + sizeof(t_zone);
		zone->next = new;
	}
	new->len = size;
	block->space -= size + sizeof(t_zone);
	new->next = 0;
	return (new->ptr);
}

void			*get_memory(char type, size_t size)
{
	void		*ptr;
	t_block		*block;

	if (type == LARGE || !(block = find_block(type, size)))
		block = create_block(type, size);
	ptr = block ? allocate_zone(block, size) : NULL;
	return (ptr);
}
