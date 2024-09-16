ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
SYMLINK := libft_malloc.so
SRC_DIR := src
OBJ_DIR := obj
SRCS := $(SRC_DIR)/malloc.c $(SRC_DIR)/free.c $(SRC_DIR)/realloc.c $(SRC_DIR)/show_alloc_mem.c $(SRC_DIR)/utils.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC := gcc
CFLAGS := -Wall -Wextra -Werror -fPIC # helps to generate position inndependent code
LDFLAGS := -shared # specifies shared library
RANDOMFLAGS := -Wl,-rpath,. # controls how the libraries are searched for
LIBRARYFLAGS := -L. -lft_malloc # specifies the library to link against

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	@rm -f $(SYMLINK)
	@ln -sf $(shell pwd)/$(NAME) $(SYMLINK)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(SYMLINK)
	@rm -f test_this
	@rm -f test_malloc1

re: fclean all

test: all
	$(CC) $(RANDOMFLAGS) -lft_malloc test/test.c -o test_this $(LIBRARYFLAGS)

run_page_test:
	@$(CC) $(RANDOMFLAGS) test/test.c -o test_page $(LIBRARYFLAGS)
	/usr/bin/time -l ./test_page
	@rm -f test_page

example: all
	gcc $(RANDOMFLAGS) test/test.c -o test_malloc1 -L. -lft_malloc

run_valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_this

.PHONY: all clean fclean re
