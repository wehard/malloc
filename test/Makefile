# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/02/24 15:56:12 by wkorande         ###   ########.fr        #
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
	@printf "Compiling $@..."
	@$(CC) $(CFLAGS) -o $@ $< $(MALLOC_SRC) $(UNITY_SRC) $(INCL) $(LIB)
	@printf "done\n"


run: re $(TARGETS)
	for test in $(TARGETS); do ./$$test || exit 1; done

clean:

fclean: clean
	@rm -f $(TARGETS)

re: fclean all

.PHONY: all clean fclean re run
