SRC = $(wildcard *.c)
FLAGS = -Werror -Wextra -Wall
LIBMLX = -lmlx -framework OpenGL -framework AppKit
OBJ = $(SRC:%.c=%.o)
NAME = cub.out

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) -g -O3 $(LIBMLX) -L. -lft $(OBJ)

bonus: $(OBJ)
	gcc -o $(NAME) -g -O3 $(LIBMLX) -L. -lft $(OBJ)

%.o: %.c
	gcc -c $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	make

.PHONY: all clean $(NAME)
