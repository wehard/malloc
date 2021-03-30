# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/03/30 11:51:22 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

BLACK=\033[30m
RED=\033[0;31m
BOLDRED=\033[1;31m
GREEN=\033[0;32m
BOLDGREEN=\033[1;32m
YELLOW=\033[0;33m
BOLDYELLOW=\033[1;33m
BLUE=\033[0;34m
BOLDBLUE=\033[1;34m
PINK=\033[0;35m
BOLDPINK=\033[1;35m
CYAN=\033[0;36m
BOLDCYAN=\033[1;36m
WHITE=\033[37m
NORMAL=\033[0m

SRCDIR = src

SRC = malloc.c\
		free.c\
		realloc.c\
		heap.c\
		block.c\
		helper.c\
		show_alloc_mem.c\
		print_memory.c\

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OUT =  $(notdir $(SRCS:.c=.o))

INCL = -I libft/includes/ -I include

LIB = -L libft -lft

CFLAGS = -Wall -Wextra -Werror

CC = clang

all: $(NAME)

$(NAME):
	@make -C libft
	@printf "$(BOLDYELLOW)%s$(NORMAL)\n" "Making $(NAME)"
	@$(CC) $(CFLAGS) $(INCL) -c $(SRCS) 
	@ar rc $(NAME) $(OUT)
	@ranlib $(NAME)
	@printf "$(YELLOW)%s$(NORMAL)\n" "done"

debug:
	@make debug -C libft
	@$(CC) -g $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

clean:
	@make clean -C libft
	@rm -rf $(OUT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)
	./RT resources/scenes/simple.csv

.PHONY: all libftmake clean fclean re run debug
