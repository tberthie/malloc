/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:28:49 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 02:41:10 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int				main(void)
{
	char		*ptr;

	ptr = malloc(128);
	memcpy(ptr, "Hello world!\0", 13);
	show_alloc_mem();
	printf("%s\n", ptr);

	ptr = realloc(ptr, 5);
	show_alloc_mem();
	printf("%s\n", ptr);

	return (0);
}
