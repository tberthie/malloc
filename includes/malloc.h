/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:39:29 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/05 18:11:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>

# define HEX			"0123456789ABCDEF"

# define TINY_MAX		64
# define SMALL_MAX		256

# define PAGE_SIZE		getpagesize()
# define ALLOC_SLOTS	150

enum e_map_types {
	TINY, SMALL, LARGE
};

typedef struct		s_map
{
	char			map_type;
	size_t			map_size; // mmap size

	struct s_map	*next;

}					t_map;

typedef struct		s_alloc
{
	char			available;
	size_t			size; // t_alloc exclu

}					t_alloc;

extern t_map		*g_map;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

t_alloc				*find_available_alloc(char type, size_t size);
t_alloc				*create_new_map(char type, size_t size);

char				get_size_type(size_t size);
size_t				get_type_size(char type);

#endif
