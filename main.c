/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:34:17 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 19:37:27 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

int		main(void)
{
	char		*str;

	str = (char*)malloc(sizeof(char) * 100);
	show_alloc_mem();
	write(1, "----------\n", 11);
	str = (char*)realloc(str, sizeof(char) * 1000);
	show_alloc_mem();
	write(1, "----------\n", 11);
	str = (char*)realloc(str, sizeof(char) * 10000);
	show_alloc_mem();

	return (0);
}
