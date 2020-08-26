# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2020/08/26 21:39:44 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = malloc_test # libft_malloc_$(HOSTTYPE).so

SRCDIR = src

SRC = malloc.c\
		free.c\
		realloc.c\
		print_memory.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(SRCS:.c=.o)

INCL = -I libft/includes/ -I include

LIB = -L libft -lft

CFLAGS = -Wall -Wextra -Werror

CC = clang

all: $(NAME)

$(NAME):
	@make -C libft
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

debug:
	# make debug -C libft
	$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

clean:
	#@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	#@make fclean -C libft

re: fclean all

run:
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)
	./RT resources/scenes/simple.csv

.PHONY: all libftmake clean fclean re run debug
