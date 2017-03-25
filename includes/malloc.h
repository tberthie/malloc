/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:39:29 by tberthie          #+#    #+#             */
/*   Updated: 2017/03/25 18:21:39 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>

# define TINY_MAX	1000
# define SMALL_MAX	10000

enum				e_type
{
	TINY, SMALL, LARGE
};

typedef struct		s_zone
{
	void			*ptr;
	size_t			len;

	struct s_zone	*next;
}					t_zone;

typedef struct		s_block
{
	void			*map;
	t_zone			*zones;

	size_t			space;
	char			type;

	char			pad[7];
	struct s_block	*next;
}					t_block;

t_block				*g_alloc;

void				*malloc(size_t size);
void				show_alloc_mem(void);

void				*get_memory(char type, size_t size);

void				print_exha(size_t nb);
void				print_size(size_t nb);
size_t				print_zones(t_block *block);

#endif
