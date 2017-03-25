/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 18:04:00 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 18:46:25 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

void			*malloc(size_t size)
{
	char			type;

	type = (size > TINY_MAX) + (size > SMALL_MAX);
	if (size <= 0)
		return (NULL);
	return (get_memory(type, size));
}

void			*realloc(void *ptr, size_t size)
{

}

void			free(void *ptr)
{

}

void			show_alloc_mem(void)
{
	t_block		*block;
	size_t		total;

	total = 0;
	block = g_alloc;
	while (block)
	{
		if (block->type == TINY)
			write(1, "TINY : ", 7);
		else if (block->type == SMALL)
			write(1, "SMALL : ", 8);
		else
			write(1, "LARGE : ", 8);
		print_exha((size_t)block->map);
		write(1, "\n", 1);
		total += print_zones(block);
		block = block->next;
	}
	write(1, "Total : ", 8);
	print_size(total);
	write(1, " octets\n", 9);
}
