
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


SRC =	src/malloc.c
CC = 		cc
CFLAG =		-Wall -Wextra -Werror
RM = 		rm -f
NAME = 		malloc.a
OBJ	= $(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C ./libft
	cp libft/libft.a $(NAME)
		@$(AR) -rcs $@ $^

%.o : %.c
	@$(CC) -c $(CFLAG) $< -o $@

all: $(NAME)

clean:
	make clean -C ./libft
	- @$(RM) $(OBJ)

fclean: clean
	make fclean -C ./libft
	- @$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re 