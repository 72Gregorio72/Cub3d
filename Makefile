NAME		= cub3D

SRCS		=	main.c \
				
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

miniclean: fclean
	$(RM) minilibx-linux

.SILENT:	all clean fclean re
.PHONY:		all clean fclean re