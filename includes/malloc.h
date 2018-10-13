/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:39:29 by tberthie          #+#    #+#             */
/*   Updated: 2018/10/13 02:46:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define HEX			"0123456789ABCDEF"
# define MIN(x, y)		(x < y ? x : y)

# define TINY_MAX		64
# define SMALL_MAX		256

# define PAGE_SIZE		getpagesize()
# define ALLOC_SLOTS	100

enum					e_zone_types {
	TINY, SMALL, LARGE
};

typedef struct			s_zone
{
	char				zone_type;
	size_t				zone_size;

	struct s_zone		*next;

}						t_zone;

typedef struct			s_zone_large
{
	char				zone_type;
	size_t				zone_size;

	struct s_zone		*next;
	size_t				size;

}						t_zone_large;

typedef struct			s_alloc
{
	char				available;
	size_t				size;

}						t_alloc;

extern t_zone			*g_zone;

void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void					show_alloc_mem(void);

void					*allocate(size_t size, char zone_type);
void					*allocate_large(size_t size);
void					*allocate_zone_slot(t_zone *zone, size_t size);
t_zone					*find_available_zone(size_t size, char zone_type);
t_zone					*create_zone(char zone_type);

t_zone					*find_ptr_zone(void *ptr);
t_alloc					*find_ptr_alloc(t_zone *zone, void *ptr);
void					free_ptr_alloc(t_zone *zone, void *ptr);
void					free_zone(t_zone *zone);
void					free_alloc(t_zone *zone, t_alloc *alloc);

void					*realloc_ptr_large(t_zone *zone, size_t size,
							void *ptr);
void					*realloc_ptr(t_zone *zone, t_alloc *alloc, size_t size,
							void *ptr);

char					get_size_type(size_t size);
size_t					get_type_size(char type);

void					store_zone(t_zone *zone);
void					print_nbr_base(unsigned int nbr, unsigned int base);
void					memcopy(char *dst, char *src, size_t len);
char					exceeds_rlimit(size_t size);

#endif
