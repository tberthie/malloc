# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2017/02/27 17:08:22 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

OBJS = $(addsuffix .o, $(addprefix objs/, malloc free realloc memory))

NAME = libft_malloc_$(HOSTTYPE).so
LNK = libft_malloc.so

all: objs $(NAME)

objs:
	mkdir objs

$(NAME): $(OBJS)
	make -C libft
	ar rc $(NAME) $(OBJS) libft/libft.a
	ln -fs $(NAME) $(LNK)

objs/%.o: srcs/%.c
	gcc -o $@ -c $< -I includes -I libft -Weverything

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)
	rm -f $(LNK)

re: fclean all
