/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:34:17 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 18:41:05 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <unistd.h>

int		main(void)
{
	char		*str;

	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);
	str = (char*)malloc(sizeof(char) * 500);

	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);
	str = (char*)malloc(sizeof(char) * 5000);

	str = (char*)malloc(sizeof(char) * 20000);
	str = (char*)malloc(sizeof(char) * 20000);
	str = (char*)malloc(sizeof(char) * 20000);
	str = (char*)malloc(sizeof(char) * 20000);
	str = (char*)malloc(sizeof(char) * 20000);

	show_alloc_mem();
	return (0);
}
