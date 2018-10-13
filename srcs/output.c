/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 23:25:54 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 01:38:02 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t		print_large(t_zone *tmp)
{
	t_zone_large	*zone;

	zone = (t_zone_large*)tmp;
	print_nbr_base((unsigned int)((char*)zone + sizeof(t_zone_large)), 16);
	write(1, " - ", 3);
	print_nbr_base((unsigned int)((char*)zone +
				sizeof(t_zone_large) + zone->size), 16);
	write(1, " : ", 3);
	print_nbr_base(zone->size, 10);
	write(1, " octets\n", 8);
	return (zone->size);
}

static size_t		print_allocs(t_zone *zone)
{
	t_alloc			*alloc;
	size_t			total;

	total = 0;
	alloc = (t_alloc*)((char*)zone + sizeof(t_zone));
	while ((char*)alloc < (char*)zone + zone->zone_size)
	{
		if (!alloc->available)
		{
			print_nbr_base((unsigned int)((char*)alloc + sizeof(t_alloc)), 16);
			write(1, " - ", 3);
			print_nbr_base((unsigned int)((char*)alloc + sizeof(t_alloc) +
						alloc->size), 16);
			write(1, " : ", 3);
			print_nbr_base(alloc->size, 10);
			write(1, " octets\n", 8);
			total += alloc->size;
		}
		alloc = (t_alloc*)((char*)alloc + sizeof(t_alloc) + alloc->size);
	}
	return (total);
}

void				show_alloc_mem(void)
{
	t_zone			*zone;
	size_t			total;

	total = 0;
	zone = g_zone;
	while (zone)
	{
		if (zone->zone_type == TINY)
			write(1, "TINY : ", 7);
		else
			write(1, zone->zone_type == SMALL ? "SMALL : " : "LARGE : ", 8);
		print_nbr_base((unsigned int)zone, 16);
		write(1, "\n", 1);
		if (zone->zone_type == LARGE)
			total += print_large(zone);
		else
			total += print_allocs(zone);
		zone = zone->next;
	}
	write(1, "Total: ", 7);
	print_nbr_base(total, 10);
	write(1, "\n", 1);
}
