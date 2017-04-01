/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:19:47 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 15:39:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone			*find_ptr(t_block *block, void *ptr)
{
	t_zone	*zone;

	zone = block->zones;
	while (zone)
	{
		if (zone->ptr == ptr)
			return (zone);
		zone = zone->next;
	}
	return (0);
}

void			mcpy(void *origin, void *dst, size_t size)
{
	while (size--)
		*(char*)dst++ = *(char*)origin++;
}

void			*zcpy(t_zone *zone, size_t size)
{
	void	*new;

	if ((new = malloc(size)))
		mcpy(zone->ptr, new, zone->len);
	free(zone->ptr);
	return (new);
}

t_block			*find_block(char type, size_t size)
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

t_zone			*find_zone(char type, size_t size)
{
	t_block		*block;
	t_zone		*zone;

	block = g_alloc;
	while (block)
	{
		if (block->type == type)
		{
			zone = block->zones;
			while (zone)
			{
				if (zone->free && zone->len >= size)
					return (zone);
				zone = zone->next;
			}
		}
		block = block->next;
	}
	return (NULL);
}
