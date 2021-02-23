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

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCL) $(LIB) -o $@ -c $(MALLOC_SRC) $(UNITY_SRC) $< 
clean:
	#@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	#@make fclean -C libft

re: fclean all

.PHONY: all libftmake clean fclean re test
