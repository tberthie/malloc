/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 01:05:09 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 02:21:31 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				free_zone(t_zone *zone)
{
	t_zone			*tmp;

	tmp = g_zone;
	if (zone == g_zone)
		g_zone = zone->next;
	else
	{
		while (tmp->next != zone)
			tmp = tmp->next;
		tmp->next = zone->next;
	}
	munmap(zone, zone->zone_size);
}

void				free_alloc(t_zone *zone, t_alloc *alloc)
{
	t_alloc			*tmp;

	tmp = (t_alloc*)((char*)zone + sizeof(t_zone));
	if (tmp != alloc)
		while ((char*)tmp + sizeof(t_alloc) + tmp->size != (char*)alloc)
			tmp = (t_alloc*)((char*)tmp + sizeof(t_alloc) + tmp->size);
	if (tmp != alloc && tmp->available)
	{
		tmp->size += sizeof(t_alloc) + alloc->size;
		alloc = tmp;
	}
	tmp = (t_alloc*)((char*)alloc + sizeof(t_alloc) + alloc->size);
	if ((char*)tmp < (char*)zone + zone->zone_size && tmp->available)
		alloc->size += tmp->size + sizeof(t_alloc);
	alloc->available = 1;
	if ((char*)alloc == (char*)zone + sizeof(t_zone) && alloc->size ==
			zone->zone_size - sizeof(t_alloc) - sizeof(t_zone))
		free_zone(zone);
}

t_zone				*find_ptr_zone(void *ptr)
{
	t_zone			*zone;

	zone = g_zone;
	while (zone)
	{
		if ((char*)ptr > (char*)zone && (char*)ptr <
				(char*)zone + zone->zone_size)
			break ;
		zone = zone->next;
	}
	return (zone);
}

t_alloc				*find_ptr_alloc(t_zone *zone, void *ptr)
{
	t_alloc			*alloc;

	if (zone->zone_type != LARGE)
	{
		alloc = (t_alloc*)((char*)zone + sizeof(t_zone));
		while ((char*)alloc < (char*)zone + zone->zone_size)
		{
			if (!alloc->available && (char*)ptr == (char*)alloc +
					sizeof(t_alloc))
				return (alloc);
			alloc = (t_alloc*)((char*)alloc + sizeof(t_alloc) + alloc->size);
		}
	}
	return (0);
}

void				free_ptr_alloc(t_zone *zone, void *ptr)
{
	t_alloc			*alloc;

	if (zone->zone_type == LARGE)
	{
		if ((char*)ptr == (char*)zone + sizeof(t_zone_large))
			free_zone(zone);
	}
	else
	{
		alloc = (t_alloc*)((char*)zone + sizeof(t_zone));
		while ((char*)alloc < (char*)zone + zone->zone_size)
		{
			if (!alloc->available && (char*)ptr == (char*)alloc +
					sizeof(t_alloc))
			{
				free_alloc(zone, alloc);
				return ;
			}
			alloc = (t_alloc*)((char*)alloc + sizeof(t_alloc) + alloc->size);
		}
	}
}
