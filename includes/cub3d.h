/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:31:52 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/19 15:48:08 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../minilibx-linux/mlx.h"
//# include "../minilibx-linux/mlx_int.h"
# include "../libft/ft_printf/ft_printf.h"
# include <math.h>
# include <fcntl.h>
# include "X11/X.h"
# include "X11/keysym.h"

# define SCREEN_X 1920
# define SCREEN_Y 1080
# define KB_W 119
# define KB_S 115
# define KB_A 97
# define KB_D 100
# define KB_ESC 65307
# define KB_UP 65362
# define KB_DOWN 65364
# define KB_LEFT 65361
# define KB_RIGHT 65363
# define RED "\033[1;31m"
# define RESET "\033[0m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.08

typedef struct s_tex {
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_tex;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map_matrix;
	int		fd_map;
	char	*N_tex;
	char	*S_tex;
	char	*W_tex;
	char	*E_tex;
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
	char	*F_tex;
	char	*C_tex;
	int		*floor_color;
	int		*ceil_color;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		camera_y;
	double		ray_dir_x;
	double		ray_dir_y;
}				t_player;

typedef struct s_img {
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_keys {
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
} t_keys;

typedef struct s_gen
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_player	player;
	t_keys		keys;
	t_map	map;
}				t_gen;

typedef struct s_ray
{
    int		x;
	double	cameraX;
	int 	mapX;
	int 	mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int 	stepX;
	int 	stepY;
	int 	hit;
	int 	side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}				t_ray;

int		close_window(t_gen *gen);
void	read_map(char **av, t_gen *gen);
void	set_player_position(t_gen *gen);
void	raycasting(t_gen *gen);
void	put_pixel(t_img *img, int x, int y, int color);
void	load_texture(void *mlx, char *path, t_tex *tex);
void	move_forward(t_gen *gen);
void	move_backward(t_gen *gen);
void	strafe_left(t_gen *gen);
void	strafe_right(t_gen *gen);
int		on_key_press(int keycode, t_gen *gen);
int		on_key_release(int keycode, t_gen *gen);
void	clear_image(t_img *img);
void	free_matrix(char **matrix, int height);

#endif