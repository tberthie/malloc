/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 23:49:06 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 01:30:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone				*create_zone(char zone_type)
{
	size_t			zone_size;
	t_zone			*zone;
	t_alloc			*alloc;

	zone_size = sizeof(t_zone) + get_type_size(zone_type) * ALLOC_SLOTS;
	if (zone_size % PAGE_SIZE)
		zone_size += PAGE_SIZE - zone_size % PAGE_SIZE;
	if ((zone = mmap(0, zone_size, PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (0);
	zone->zone_type = zone_type;
	zone->zone_size = zone_size;
	zone->next = 0;
	alloc = (t_alloc*)((char*)zone + sizeof(t_zone));
	alloc->available = 1;
	alloc->size = zone_size - sizeof(t_zone) - sizeof(t_alloc);
	store_zone(zone);
	return (zone);
}
