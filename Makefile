ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME := libft_malloc_$(HOSTTYPE).so
SYMLINK := libft_malloc.so
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
SRC_DIR := src
OBJ_DIR := obj
SRCS := $(SRC_DIR)/malloc.c $(SRC_DIR)/free.c $(SRC_DIR)/realloc.c $(SRC_DIR)/show_alloc_mem.c $(SRC_DIR)/utils.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC := gcc
CFLAGS := -Wall -Wextra -Werror -fPIC # good for shaderd memory acsess
LDFLAGS := -shared

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@ln -sf $(NAME) $(SYMLINK) # creates a symbold link to the library to recogine with -L. -lft_malloc flag 

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(SYMLINK)

re: fclean all

test: all
	@$(CC) -I $(LIBFT_DIR) -L . -Wl,-rpath,. -lft_malloc test/test.c -o test_this
	@./test_this
	# @valgrind --read-var-info=yes --leak-check=full --track-origins=yes ./test_this
	@rm -f test_this

example:
	gcc -o test_malloc1 test/test.c -L. -lft_malloc

.PHONY: all clean fclean re