NAME		= cub3D

SRCS		=	main.c \
				free.c \
				map_loader.c \
				player_loader.c \
				raycasting.c \
				utils_map_loader.c \
				check_map.c \
				check_map1.c \
				utils_map_check.c \
				utils_ray.c \
				utils_ray2.c \
				utils_ray3.c \
				utils_ray4.c \
				

OBJS		= $(SRCS:.c=.o)

INCLUDES = -Iincludes

CC = cc
MLX = -Lminilibx-linux minilibx-linux/libmlx_Linux.a -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz
CFLAGS	= -Wall -Werror -Wextra -g

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft --quiet
	@$(MAKE) -C ./minilibx-linux --quiet
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(MLX) ./libft/libft.a -o $(NAME)

%.o: %.c
	if [ ! -d "minilibx-linux" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git; \
	fi
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C ./libft clean --quiet
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C ./libft fclean
	@$(RM) $(NAME)

re: fclean all

bonus: all
	@echo Go to bonus dir

miniclean: fclean
	$(RM) minilibx-linux

valgrind: re clean
	@clear
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) ciao.cub

.SILENT:	all clean fclean re
.PHONY:		all clean fclean re