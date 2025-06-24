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

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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

typedef struct s_tex
{
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
	char	*n_tex;
	char	*s_tex;
	char	*w_tex;
	char	*e_tex;
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
	char	*f_tex;
	char	*c_tex;
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

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_gen
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_player	player;
	t_keys		keys;
	char		player_orientation;
	t_map		map;
}				t_gen;

typedef struct s_ray
{
	int		x;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	delta_distx;
	double	delta_disty;
	double	side_distx;
	double	side_disty;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_ray;

int		close_window(t_gen *gen);
int		read_map(char **av, t_gen *gen);
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
int		parsing_map(t_gen *gen);
int		get_texture_paths(char *file, t_gen *gen);
int		get_char_pos(char *src, int c);
int		map_check(t_gen *gen);
int		check_closed(t_gen *gen);
void	clean_path(char *path);
void	free_gen(t_gen *gen, int flag);
void	draw_map_col(t_ray *ray, t_gen *gen);
void	calculate_distance(t_ray *ray, t_gen *gen);
void	check_hit(t_ray *ray, t_gen *gen);
void	init_ray(t_ray *ray, t_gen *gen);
void	get_step(t_ray *ray, t_gen *gen);
t_tex	*select_texture(t_ray *ray, t_gen *gen);
void	clear_image(t_img *img);
int		pre_checks(int ac, char **av, t_gen *gen);
void	clean_path(char *path);
void	load_texture(void *mlx, char *path, t_tex *tex);
void	put_pixel(t_img *img, int x, int y, int color);
void	init_image(t_gen *gen);
void	rotate_player(t_gen *gen, double angle);
int		is_walkable(t_gen *gen, double x, double y);
void	check_movements_util(t_gen *gen);
void	check_movements(t_gen *gen);
void	update_player_position(int keysym, t_gen *gen);
void	rotate_view(t_gen *gen);
void	read_file(int fd, int i, t_gen *gen, int y);
void	get_map_dimensions(char *file, t_map *map);
void	fill_map_row(t_gen *gen, char *line, int y);
int		unclosed_zero(t_map *map);
void	draw_minimap(t_map *map, t_gen *gen);

#endif