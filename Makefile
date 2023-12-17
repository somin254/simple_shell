CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = _atoi.c \
      builtin1.c \
      environ.c \
      errors.c \
      getenv.c \
      getline.c \
      list1.c \
      main.c \
      parser.c \
      realloc.c \
      shell_loop.c \
      str.c \
      vars.c

OBJ = $(SRC:.c=.o)
TARGET = hsh

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re

