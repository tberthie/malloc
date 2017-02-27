/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:21:37 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 14:59:19 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
	ptr = 0;
	if (size <= 0 || (!g_init && !setup()))
		return (ptr);
//	if (!ptr)
	size = 0;
	ptr = NULL;
	return (ptr);
}
