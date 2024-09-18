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
CFLAGS := -Wall -Wextra -Werror -fPIC -I. # helps to generate position inndependent code the fPic flag
LDFLAGS := -shared # specifies shared library
LIBRARYFLAGS := -L. -lft_malloc # specifies the library to link against

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@LD_PRELOAD=./libft_malloc.so
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "Creating symlink $(SYMLINK) pointing to $(shell pwd)/$(NAME)"
	@rm -f $(SYMLINK)
	@ln -sf $(shell pwd)/$(NAME) $(SYMLINK)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(SYMLINK)
	@rm -f test_this
	@rm -f test_malloc1

re: fclean all

run_page_test:
	@$(CC) test.c -o test_page $(LIBRARYFLAGS)
	/usr/bin/time -l ./test_page
	@rm -f test_page


.PHONY: all clean fclean re
