/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:21:29 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 17:05:21 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*malloc(size_t size)
{
	void	*ptr;
	char	type;

	if (size > SMALL_MAX)
		type = LARGE;
	else
		type = size > TINY_MAX ? SMALL : TINY;
	ptr = 0;
	if (size <= 0 || (!g_init && !setup()))
		return (ptr);
	if (!find_zone(size, &ptr, type))
		alloc_zone(size, &ptr, type);
	return (ptr);
}
