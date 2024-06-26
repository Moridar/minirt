# Makefile for minrt
# Author: Bobbie Syvasalmi 
# Version 1.0
# Date: 04/04/2024

NAME = minirt

LIBFTDIR = libft/
LIBFT = libft/libft.a
MLX42 = MLX42/build/libmlx42.a

SRCS = 	main.c \
		camera.c light.c \
		draw.c \
		draw_light.c \
		events.c \
		utils.c \
		hitable_create.c \
		hitable_hit.c \
		hitable_hit_cone.c \
		hitable_hit_getcolor.c \
		validator.c \
		validator_parse_hitable.c \
		validator_parse_other.c \
		validator_parse_utils.c \
		validator_validate.c \
		validator_validate_extra.c \
		color.c

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRCS))

VEC3SRCS = baseoperator.c moreoperators.c
VEC3_DIR = src/vec3/
VEC3 = $(addprefix $(VEC3_DIR), $(VEC3SRCS))

OBJ_DIR = obj/
VEC3OBJ_DIR = obj/vec3/
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o)) $(addprefix $(VEC3OBJ_DIR), $(VEC3SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror -IMLX42/include -Ilibft -Iinclude -O3

MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
WSLFLAGS = -L$(LIBFTDIR) -lft -ldl -lglfw -pthread -lm  

all: $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJ_DIR) $(VEC3OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(MLXFLAGS) $(OBJ) libft/libft.a MLX42/build/libmlx42.a -o $(NAME)

wsl: $(MLX42) $(LIBFT) $(OBJ_DIR) $(VEC3OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(OBJ) MLX42/build/libmlx42.a $(WSLFLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(VEC3OBJ_DIR):
	mkdir $(VEC3OBJ_DIR)

$(MLX42):
	cmake MLX42/ -B MLX42/build && make -C MLX42/build -j4

$(LIBFT):
	make -C libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	rm -rf MLX42/build
	rm -rf $(LIBFT)

re: fclean all

.phony:: all clean fclean re