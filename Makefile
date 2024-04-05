# Makefile for minrt
# Author: Bobbie Syvasalmi 
# Version 1.0
# Date: 04/04/2024

NAME = minirt

SRCS = main.c camera.c draw.c events.c hitable.c light.c
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRCS))

LIBFTDIR = libft/
LIBFT = libft/libft.a
MLX42 = MLX42/build/libmlx42.a

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -IMLX42/include -Ilibft -Iinclude

MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
WSLFLAGS = -L$(LIBFTDIR) -lft -ldl -lglfw -pthread -lm  

all: $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(MLXFLAGS) $(OBJ) libft/libft.a MLX42/build/libmlx42.a -o $(NAME)

wsl: $(MLX42) $(LIBFT) $(OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(OBJ) MLX42/build/libmlx42.a $(WSLFLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(MLX42):
	cmake MLX42/ -B MLX42/build && make -C MLX42/build -j4

$(LIBFT):
	make -C libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf MLX42/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.phony:: all clean fclean re