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

# define TINY_MAX	40
# define SMALL_MAX	4000

enum			e_type
{
	TINY, SMALL, LARGE
};

typedef struct	s_zone
{
	void		*ptr;
	size_t		len;
	int			offset;
	char		padding[4];
}				t_zone;

typedef struct	s_block
{
	size_t		size;
	size_t		free_space;
	t_zone		**zones;
}				t_block;

static struct	s_alloc
{
	t_block		**tiny;
	t_block		**small;
	t_block		**large;
}				g_alloc;

static char		g_init = 0;

char			setup(void);

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);

void			*map_memory(void *addr, size_t len, char block);
char			find_zone(size_t size, void **ptr, char type);
void			alloc_zone(size_t size, void **ptr, char type);

#endif
