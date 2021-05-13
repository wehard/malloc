# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/05/13 14:15:50 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LINK = libft_malloc.so
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
OBJDIR = obj

SRC = block.c\
		free.c\
		ft_memcpy.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_strlen.c\
		heap.c\
		helper.c\
		malloc.c\
		print_memory.c\
		realloc.c\
		show_alloc_mem.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(SRC:%.c=$(OBJDIR)/%.o)

INCL = -I include

LIB = #-L libft -lft

CFLAGS = -Wall -Wextra -Werror -fPIC

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)Creating $(NAME)..."
	@$(CC) -shared -o $@ $(OBJS)
	@printf "done$(NORMAL)\n"
	@printf "$(CYAN)Creating symlink $(LINK) -> $(NAME)..."
	@ln -fs $(NAME) $(LINK)
	@printf "done$(NORMAL)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g $(INCL)
	
clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LINK)

re: fclean all

run:
	$(CC) $(CFLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)
	./RT resources/scenes/simple.csv

.PHONY: all clean fclean re
