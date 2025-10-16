NAME = miniRT

SRC = main.c \
	parsing/parsing.c parsing/parce_sphere.c parsing/parse_line.c \
	parsing/parse_colors_vectors.c parsing/parse_plan.c parsing/parse_ambient.c\
	\
	get_next_line/get_next_line_utils.c get_next_line/get_next_line.c \
	\
	utils/ft_atof.c utils/memory_utils.c utils/new_spher.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

libft = Libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	make -C Libft/
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

clean :
	make clean -C Libft/
	rm -rf $(OBJ)

fclean : clean
	make fclean -C Libft/
	rm -rf $(NAME)

re : fclean all