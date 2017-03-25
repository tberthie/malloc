/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:19:47 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/26 00:27:58 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			fix_gap(t_zone *zone, size_t gap)
{
	while (zone && zone->next)
	{
		mcpy(zone->next, (void*)zone->ptr + zone->len - gap,
		zone->next->len + sizeof(t_zone));
		zone->next = (void*)zone->ptr + zone->len - gap;
		zone->next->ptr = (void*)zone->next + sizeof(t_zone);
		zone = zone->next;
	}
}

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

void			remove_zone(t_zone *zone, t_block *block)
{
	if (zone->next)
		zone->next->prev = zone->prev;
	if (zone->prev)
	{
		zone->prev->next = zone->next;
		fix_gap(zone->prev, zone->len + sizeof(t_zone));
	}
	else if (zone->next)
	{
		mcpy(zone->next, block->map, zone->next->len + sizeof(t_zone));
		block->zones = block->map;
		block->zones->ptr = block->map + sizeof(t_zone);
		fix_gap(block->zones, zone->len + sizeof(t_zone));
	}
}
