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
CFLAGS := -Wall -Wextra -Werror -fPIC
LDFLAGS := -shared

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

re: fclean all

test: all
	@$(CC) -L . -Wl,-rpath,. -lft_malloc test/test.c -o test_this

run_page_test:
	@$(CC) -L . -Wl,-rpath,. -lft_malloc test/test.c -o test_page
	/usr/bin/time -l ./test_page
	@rm -f test_page

example:
	gcc -o test_malloc1 test/test.c -L. -lft_malloc

.PHONY: all clean fclean re
