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
CFLAGS := -Wall -Wextra -Werror -fPIC # helps to generate position inndependent code the fPic flag
LDFLAGS := -shared # specifies shared library
LIBRARYFLAGS := -L. -lft_malloc # specifies the library to link against
PATHINC := include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)
	@ln -sf $(NAME) $(SYMLINK)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(PATHINC)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(SYMLINK)
	@rm -f test_this
	@rm -f test_malloc1
	@rm -f test_page

re: fclean all

run_page_test:
	@$(CC) test.c -o test_page $(LIBRARYFLAGS)
	/usr/bin/time -l ./test_page
	@rm -f test_page

.PHONY: all clean fclean re
