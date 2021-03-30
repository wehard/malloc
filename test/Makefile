# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/03/30 11:53:48 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

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

MALLOC_SRC = ../src/*.c
UNITY_SRC = ../vendor/Unity/src/*.c

LIB = -L ../libft -lft -lpthread -L ../ -lft_malloc_$(HOSTTYPE)

CFLAGS = -Wall -Wextra -Werror

CC = clang

TEST_DIR = .

TESTS = $(wildcard $(TEST_DIR)/*.c)
TARGETS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%,$(TESTS))

INCL = -I ../libft/includes -I ../include -I ../vendor/Unity/src

FAILED=none

all: $(TARGETS)

$(TARGETS): %: %.c
	@printf "Compiling $@..."
	@$(CC) $(CFLAGS) -o $@ $< $(MALLOC_SRC) $(UNITY_SRC) $(INCL) $(LIB)
	@printf "done\n"


run: re $(TARGETS)
	@for test in $(TARGETS); do ./$$test | tee $$test.testpass; printf "\n" || (echo "$(BOLDRED)$$test$(NORMAL)"); done
	@ruby ../vendor/Unity/auto/unity_test_summary.rb .

run2: re $(TARGETS)
	$(foreach test,$(TARGETS),./$(test);)
	@ruby ../vendor/Unity/auto/unity_test_summary.rb .

clean:
	@rm -f *.testpass
	@rm -f *.testfail

fclean: clean
	@rm -f $(TARGETS)

re: fclean all

.PHONY: all clean fclean re run
