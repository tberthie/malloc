/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 23:16:45 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 03:17:47 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				print_nbr_base(size_t nbr, unsigned int base)
{
	size_t			i;

	i = 1;
	if (base == 16)
		write(1, "0x", 2);
	while (nbr / i >= base)
		i *= base;
	while (i)
	{
		write(1, &HEX[nbr / i % base], 1);
		i /= base;
	}
}

void				store_zone(t_zone *zone)
{
	t_zone			*tmp;

	if (!g_zone || zone < g_zone)
	{
		zone->next = g_zone;
		g_zone = zone;
		return ;
	}
	tmp = g_zone;
	while (tmp->next)
	{
		if (tmp->next > zone)
			break ;
		tmp = tmp->next;
	}
	zone->next = tmp->next;
	tmp->next = zone;
}

void				memcopy(char *dst, char *src, size_t len)
{
	while (len--)
		*dst++ = *src++;
}

char				exceeds_rlimit(size_t size)
{
	struct rlimit	limit;

	if (getrlimit(RLIMIT_MEMLOCK, &limit) == -1 || size > limit.rlim_cur)
		return (1);
	return (0);
}

size_t				min(size_t a, size_t b)
{
	return (a > b ? b : a);
}
