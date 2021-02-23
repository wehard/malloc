# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/02/23 18:03:40 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MALLOC_SRC = ../src/*.c
UNITY_SRC = ../vendor/Unity/src/*.c

LIB = -L ../libft -lft

CFLAGS = -Wall -Wextra -Werror

CC = clang

TEST_DIR = .

TESTS = $(wildcard $(TEST_DIR)/*.c)
TARGETS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%,$(TESTS))

INCL = -I ../libft/includes -I ../include -I ../vendor/Unity/src

all: $(TARGETS)

$(TARGETS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(MALLOC_SRC) $(UNITY_SRC) $(INCL) $(LIB)

clean:
	#@make clean -C libft

fclean: clean
	@rm -f $(TARGETS)

re: fclean all

.PHONY: all libftmake clean fclean re test
