/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:39:29 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 19:48:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>

# define PAGE		getpagesize()

# define TINY_MAX	(size_t)(PAGE / 16)
# define SMALL_MAX	(size_t)(PAGE / 4)

enum				e_type
{
	TINY, SMALL, LARGE
};

typedef struct		s_zone
{
	void			*ptr;
	size_t			len;

	struct s_zone	*prev;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_block
{
	void			*map;
	t_zone			*zones;

	size_t			space;
	char			type;

	char			pad[7];
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

t_block				*g_alloc;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);

void				*get_memory(char type, size_t size);

void				print_exha(size_t nb);
void				print_size(size_t nb);
size_t				print_zones(t_block *block);

void				mcpy(void *origin, void *dst, size_t size);
t_zone				*find_ptr(t_block *block, void *ptr);
void				fix_gap(t_zone *zone, size_t gap);
void				*zcpy(void *ptr);

#endif
