SRC = $(wildcard *.c)

OBJ = $(SRC:%.c=%.o)

all: compile

compile: $(OBJ)
	gcc -lmlx -framework OpenGL -framework AppKit -L. -lft $(OBJ)

%.o: %.c
	gcc -c $^ -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean compile
