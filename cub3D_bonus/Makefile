NAME		= cub3D_bonus

SRCS		=	main_bonus.c \
				\
				srcs/free_bonus.c \
				srcs/free_utils_bonus.c \
				srcs/player_loader_bonus.c \
				srcs/init_bonus.c \
				srcs/key_listener_bonus.c \
				\
				map_loader/utils_map_loader_bonus.c \
				map_loader/check_map_bonus.c \
				map_loader/check_map1_bonus.c \
				map_loader/utils_map_check_bonus.c \
				map_loader/minimap_bonus.c \
				map_loader/map_loader_bonus.c \
				map_loader/minimap_arrow_bonus.c \
				map_loader/minimap_grid_bonus.c \
				map_loader/minimap_zombie_bonus.c \
				\
				raycasting/raycasting_bonus.c \
				raycasting/utils_ray_bonus.c \
				raycasting/utils_ray2_bonus.c \
				raycasting/utils_ray3_bonus.c \
				raycasting/utils_ray4_bonus.c \
				raycasting/utils_ray5_bonus.c \
				raycasting/draw_minigame_bonus.c \
				\
				minigame/zombie_cpu_bonus.c \
				minigame/fps_bonus.c \
				minigame/zombie_utils_bonus.c \
				\
				ui/draw_healthbar_bonus.c \
				\
				animator/zombie_animator_bonus.c \
				

OBJS		= $(SRCS:.c=.o)

ARSG		= maps/test.cub

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

vale: re
	make clean
	@clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARSG)

push: miniclean
	bash -i -c "push"

test: re
	make clean
	@clear
	@./$(NAME) $(ARSG)

.SILENT:	all clean fclean re
.PHONY:		all clean fclean re