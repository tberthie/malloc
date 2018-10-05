/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:15:09 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/05 17:48:03 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map			*g_map = 0;

void			free(void *ptr)
{
}

void			*malloc(size_t size)
{
	t_alloc		*alloc;
	char		type;

	type = get_size_type(size);
	if (type != LARGE && (alloc = find_available_alloc(type, size)))
		return ((char*)alloc + sizeof(t_alloc));
	if ((alloc = create_new_map(type, size)))
	{
		if (type == LARGE)
			return ((char*)alloc + sizeof(t_map));
		return ((char*)alloc + sizeof(t_alloc));
	}
	return (0);
}

void			*realloc(void *ptr, size_t size)
{

}
