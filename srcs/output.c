/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:19:30 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 18:25:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

void			print_exha(size_t nb)
{
	char	c;
	size_t	i;

	write(1, "0x", 2);
	i = 1;
	while (nb / i > 15)
		i *= 16;
	while (i)
	{
		c = ("0123456789ABCDEF")[nb / i % 16];
		write(1, &c, 1);
		i /= 16;
	}
}

void			print_size(size_t nb)
{
	char	c;
	size_t	i;

	i = 1;
	while (nb / i > 9)
		i *= 10;
	while (i)
	{
		c = nb / i % 10 + '0';
		write(1, &c, 1);
		i /= 10;
	}
}

size_t			print_zones(t_block *block)
{
	t_zone	*zone;
	size_t	total;

	total = 0;
	zone = block->zones;
	while (zone)
	{
		print_exha((size_t)zone->ptr);
		write(1, " - ", 3);
		print_exha((size_t)(zone->ptr + zone->len));
		write(1, " : ", 3);
		print_size(zone->len);
		total += zone->len;
		write(1, " octets\n", 8);
		zone = zone->next;
	}
	return (total);
}
