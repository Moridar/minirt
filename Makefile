# Makefile for minrt
# Author: Bobbie Syvasalmi 
# Version 1.0
# Date: 04/04/2024

NAME = minirt

LIBFT = libft/libft.a
LIBFTDIR = ./libft
LIBMLXDIR = ./minilibx-linux
SRC = main.c events.c set.c
OBJ = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bsyva: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft -L$(LIBMLXDIR) -lmlx -lX11 -lXext -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	@rm -rf *.o
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	
re: fclean all

.phony:: all clean fclean re