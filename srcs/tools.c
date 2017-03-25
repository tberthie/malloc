/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:19:47 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 19:30:36 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			fix_gap(t_zone *zone, size_t gap)
{
	while (zone && zone->next)
	{
		mcpy(zone->next, zone->ptr + zone->len - gap,
		zone->next->len + sizeof(t_zone));
		zone->next = zone->ptr + zone->len - gap;
		zone->next->ptr = zone->next + sizeof(t_zone);
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
