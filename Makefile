NAME = miniRT

SRC = main.c \
	parsing/parsing.c parsing/parse_sphere.c parsing/parse_line.c parsing/parse_camera.c parsing/parse_cylinder.c \
	parsing/parse_colors_vectors.c parsing/parse_plan.c parsing/parse_ambient.c parsing/parse_light.c \
	parsing/parse_cone.c parsing/parse_triangle.c parsing/parse_disk.c \
	get_next_line/get_next_line_utils.c get_next_line/get_next_line.c \
	utils/ft_atof.c utils/memory_utils.c utils/new_spher.c utils/helper_functions.c utils/tokenizer.c utils/texture_cleanup.c\
	srcs/init.c srcs/draw.c srcs/hooks.c srcs/render.c srcs/ray.c srcs/vector_math_1.c srcs/camera.c\
	srcs/hit.c srcs/cylinder_intersect.c srcs/intersect.c srcs/sphere_intersect.c srcs/plane_intersect.c\
	srcs/lighting.c srcs/shadow.c srcs/disk_intersect.c srcs/triangle_intersect.c srcs/cone_intersect.c\
	srcs/vector_math_2.c srcs/light_util.c srcs/bump_mapping.c srcs/texture.c srcs/uv_mapping.c\

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3 -I/usr/local/include

LIBFT = Libft/libft.a
MLX_FLAGS = -L/usr/local/lib -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)
	make clean

$(NAME): $(OBJ)
	make -C Libft/
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	make clean -C Libft/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C Libft/
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
