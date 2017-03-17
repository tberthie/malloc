/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 13:05:58 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 17:07:11 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include "libft.h"

void			*map_memory(void *addr, size_t len, char block)
{
	void		*ptr;

	ptr = mmap(addr, len, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (ptr == MAP_FAILED)
		ft_printf(2, "malloc: map failed (size=%d)\n\
		can't allocate region\n", len);
	return (ptr);
}

char			find_zone(size_t size, void **ptr, char type)
{
}

void			alloc_zone(size_t size, void **ptr, char type)
{
	t_block		*block;

	if (!(block = map_memory(NULL, sizeof(t_block), 1)))
		return ;
}

