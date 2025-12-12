NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./ -Imlx_linux
AR = ar rcs
RM = rm -f

SRC = FdF.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	cp libft/libft.a $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -L./libft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
