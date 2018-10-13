/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 02:42:46 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 02:47:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc_ptr_large(t_zone *zone, size_t size, void *ptr)
{
	void		*new_ptr;

	if (zone->zone_type != get_size_type(size) ||
			size > zone->zone_size - sizeof(t_zone_large))
	{
		if ((new_ptr = malloc(size)))
			memcopy(new_ptr, ptr, MIN(size, ((t_zone_large*)zone)->size));
		free_zone(zone);
		return (new_ptr);
	}
	else
		((t_zone_large*)zone)->size = size;
	return (ptr);
}

void		*realloc_ptr(t_zone *zone, t_alloc *alloc, size_t size, void *ptr)
{
	void		*new_ptr;

	if (zone->zone_type != get_size_type(size) || size > alloc->size)
	{
		if ((new_ptr = malloc(size)))
			memcopy(new_ptr, ptr, MIN(size, alloc->size));
		free_alloc(zone, alloc);
		return (new_ptr);
	}
	return (ptr);
}
