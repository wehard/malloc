# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <willehard@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 15:48:04 by rjaakonm          #+#    #+#              #
#    Updated: 2021/03/30 15:03:55 by wkorande         ###   ########.fr        #
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

LIB = -L ../ -lft_malloc_$(HOSTTYPE) -L ../libft -lft -lpthread

CFLAGS = -Wall -Wextra -Werror

CC = clang

TEST_DIR = .

TESTS = $(wildcard $(TEST_DIR)/*.c)
SUBJECT_TESTS = $(wildcard $(TEST_DIR)/test_subject_*.c)

TARGETS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%,$(TESTS))

SUBJECT_TARGETS = $(patsubst $(TEST_DIR)/%.c,$(TEST_DIR)/%,$(SUBJECT_TESTS))

INCL = -I ../libft/includes -I ../include -I ../vendor/Unity/src

FAILED=none

all: lib $(TARGETS)

$(TARGETS): %: %.c
	@printf "Compiling $@..."
	@$(CC) -g $(CFLAGS) $(INCL) $(UNITY_SRC) -o $@ $< $(LIB)
	@printf "done\n"

run: re $(TARGETS)
	@printf "\n$(BOLDBLUE)--- BEGIN TESTS ---$(BLUE)\n"
	@for test in $(TARGETS); do ./$$test | tee $$test.testpass; printf "\n" || (printf "$(BOLDRED)$$test$(NORMAL)"); done
	@printf "\n$(BOLDBLUE)--- END TESTS ---$(NORMAL)\n"
	@ruby ../vendor/Unity/auto/unity_test_summary.rb .

subject: fclean $(SUBJECT_TARGETS)
	@printf "\n$(BOLDBLUE)--- BEGIN TESTS ---$(BLUE)\n"
	@for test in $(SUBJECT_TARGETS); do ./$$test | tee $$test.testpass; printf "\n" || (printf "$(BOLDRED)$$test$(NORMAL)"); done
	@printf "\n$(BOLDBLUE)--- END TESTS ---$(NORMAL)\n"
	@ruby ../vendor/Unity/auto/unity_test_summary.rb .

run2: re $(TARGETS)
	$(foreach test,$(TARGETS),./$(test);)
	@ruby ../vendor/Unity/auto/unity_test_summary.rb .

lib:
	@make -C ..

clean:
	@rm -f *.testpass
	@rm -f *.testfail

fclean: clean
	@rm -f $(TARGETS)
	@rm -f $(SUBJECT_TARGETS)

re: fclean all

.PHONY: all clean fclean re run
