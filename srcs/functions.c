/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:15:09 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 02:47:08 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone			*g_zone = 0;

void			free(void *ptr)
{
	t_zone		*zone;

	if (ptr && (zone = find_ptr_zone(ptr)))
		free_ptr_alloc(zone, ptr);
}

void			*malloc(size_t size)
{
	char		zone_type;

	if (exceeds_rlimit(size))
		return (0);
	zone_type = get_size_type(size);
	if (zone_type == LARGE)
		return (allocate_large(size));
	return (allocate(size, zone_type));
}

void			*realloc(void *ptr, size_t size)
{
	t_zone		*zone;
	t_alloc		*alloc;

	if (exceeds_rlimit(size))
		return (0);
	if ((zone = find_ptr_zone(ptr)))
	{
		if (zone->zone_type == LARGE)
			return (realloc_ptr_large(zone, size, ptr));
		else if ((alloc = find_ptr_alloc(zone, ptr)))
			return (realloc_ptr(zone, alloc, size, ptr));
	}
	return (0);
}
