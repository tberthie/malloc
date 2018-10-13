/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 23:01:10 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 02:55:48 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone				*find_available_zone(size_t size, char zone_type)
{
	t_zone			*zone;
	t_alloc			*alloc;

	zone = g_zone;
	while (zone)
	{
		if (zone->zone_type == zone_type)
		{
			alloc = (t_alloc*)((char*)zone + sizeof(t_zone));
			while ((char*)alloc < (char*)zone + zone->zone_size)
			{
				if (alloc->available && (alloc->size >= size +
							sizeof(t_alloc) || alloc->size >= size))
					return (zone);
				alloc = (t_alloc*)((char*)alloc +
						sizeof(t_alloc) + alloc->size);
			}
		}
		zone = zone->next;
	}
	return (0);
}

void				*allocate_zone_slot(t_zone *zone, size_t size)
{
	t_alloc			*alloc;
	void			*end;

	alloc = (t_alloc*)((char*)zone + sizeof(t_zone));
	while ((char*)alloc < (char*)zone + zone->zone_size)
	{
		if (alloc->available && alloc->size >= size + sizeof(t_alloc))
		{
			end = (char*)alloc + sizeof(t_alloc) + alloc->size;
			alloc->available = 0;
			alloc->size = size;
			alloc = (t_alloc*)((char*)alloc +
					sizeof(t_alloc) + alloc->size);
			alloc->available = 1;
			alloc->size = (char*)end - ((char*)alloc + sizeof(t_alloc));
			return ((t_alloc*)((char*)alloc - size));
		}
		else if (alloc->available && alloc->size >= size)
		{
			alloc->available = 0;
			return ((char*)alloc + sizeof(t_alloc));
		}
		alloc = (t_alloc*)((char*)alloc + sizeof(t_alloc) + alloc->size);
	}
	return (0);
}

void				*allocate(size_t size, char zone_type)
{
	t_zone			*zone;

	if ((zone = find_available_zone(size, zone_type)))
		return (allocate_zone_slot(zone, size));
	else if ((zone = create_zone(zone_type)))
		return (allocate_zone_slot(zone, size));
	return (0);
}

void				*allocate_large(size_t size)
{
	size_t			zone_size;
	t_zone_large	*zone;

	zone_size = sizeof(t_zone_large) + size;
	if (zone_size % PAGE_SIZE)
		zone_size += PAGE_SIZE - zone_size % PAGE_SIZE;
	if ((zone = mmap(0, zone_size, PROT_READ | PROT_WRITE, MAP_ANON |
					MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (0);
	zone->zone_type = LARGE;
	zone->zone_size = zone_size;
	zone->next = 0;
	zone->size = size;
	store_zone((t_zone*)zone);
	return ((char*)zone + sizeof(t_zone_large));
}
