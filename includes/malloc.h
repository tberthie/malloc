/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:39:29 by tberthie          #+#    #+#             */
/*   Updated: 2017/02/27 17:09:37 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>

# define TINY_SIZE	4096
# define SMALL_SIZE	409600

# define TINY_MAX	(TINY_SIZE / 150)
# define SMALL_MAX	(SMALL_SIZE / 150)

enum			e_type
{
	TINY,
	SMALL,
	LARGE
};

typedef struct	s_zone
{
	void			*ptr;
	size_t			len;
	struct s_zone	*next;
}				t_zone;

typedef struct	s_block
{
	t_zone			*zones; // free zones with occupied zones list
	struct s_block	*next;
}				t_block; // malloc with the block 

typedef struct	s_alloc
{
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
}				t_alloc;

static t_alloc	g_alloc = {.tiny = 0, .small = 0, .large = 0};

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);

void			*map_memory(void *addr, size_t len, char block);
char			find_zone(size_t size, void **ptr, char type);
void			alloc_zone(size_t size, void **ptr, char type);

#endif
