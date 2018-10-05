/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:04:35 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/05 16:30:30 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char				get_size_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	return (size <= SMALL_MAX ? SMALL : LARGE);
}

size_t				get_type_size(char type)
{
	return (type == TINY ? TINY_MAX : SMALL_MAX);
}
