# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/05/13 15:57:31 by wkorande         ###   ########.fr        #
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

CC = gcc

# ----------------------------------------
#                LIBRARY
# ----------------------------------------

LIB_SRCDIR = src
LIB_OBJDIR = obj

LIB_SRC = block.c\
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
		show_alloc_mem.c\
		ft_bzero.c

LIB_SRCS = $(addprefix $(LIB_SRCDIR)/, $(LIB_SRC))
LIB_OBJS = $(LIB_SRC:%.c=$(LIB_OBJDIR)/%.o)
LIB_INCLUDE = -I include
LIB_CFLAGS = -Wall -Wextra -Werror -fPIC

# ----------------------------------------
#                TESTS
# ----------------------------------------

UNITY_SRC = ./vendor/Unity/src/*.c
TEST_DIR = test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_TARGETS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%,$(TEST_SRCS))
TEST_DSYM =  $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%.dSYM,$(TEST_SRCS))

TEST_INCL = -I include -I vendor/Unity/src
TEST_CFLAGS = -g -O0 #-Wall -Wextra -Werror

# ----------------------------------------
#                RULES
# ----------------------------------------

all: $(NAME)

$(NAME): $(LIB_OBJS)
	@printf "$(YELLOW)Creating $(NAME)..."
	@$(CC) -shared -o $@ $(LIB_OBJS)
	@printf "done$(NORMAL)\n"
	@printf "$(CYAN)Creating symbolic link: $(LINK) -> $(NAME)..."
	@ln -fs $(NAME) $(LINK)
	@printf "done$(NORMAL)\n"

$(LIB_OBJDIR)/%.o: $(LIB_SRCDIR)/%.c
	@mkdir -p $(LIB_OBJDIR)
	@$(CC) -c -o $@ $(LIB_CFLAGS) $^ -O0 -g $(LIB_INCLUDE)
	

test: re $(TEST_TARGETS)
	@printf "\n$(BOLDBLUE)--- BEGIN TESTS ---$(BLUE)\n"
	@for test in $(TEST_TARGETS); do ./$$test | tee $$test.testpass; printf "\n" || (printf "$(BOLDRED)$$test$(NORMAL)"); done
	@printf "\n$(BOLDBLUE)--- END TESTS ---$(NORMAL)\n"
	@ruby ./vendor/Unity/auto/unity_test_summary.rb $(TEST_DIR)/.

$(TEST_TARGETS): %: %.c
	@printf "Compiling $@..."
	@$(CC) $(TEST_CFLAGS) $(TEST_INCL) $(UNITY_SRC) -o $@ $< -L . -lft_malloc -lpthread
	@printf "done\n"

clean:
	@rm -rf $(LIB_OBJDIR)
	@rm -f $(TEST_TARGETS)
	@rm -rf $(TEST_DSYM)
	@rm -f $(TEST_DIR)/*.testpass
	@rm -f $(TEST_DIR)/*.testfail

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LINK)

re: fclean all

.PHONY: all clean fclean re
