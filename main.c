/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:34:17 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 19:31:16 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

int		main(void)
{
	char		*str;
	char		*str2;

	str = (char*)malloc(sizeof(char) * 500);
	str2 = (char*)malloc(sizeof(char) * 500);
	show_alloc_mem();

	str = (char*)realloc(str, sizeof(char) * 100);
	str = (char*)malloc(sizeof(char) * 500);
	show_alloc_mem();

	return (0);
}
