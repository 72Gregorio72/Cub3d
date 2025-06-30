/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:40:18 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/26 12:40:18 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef M_PI_4
#  define M_PI_4 0.78539816
# endif

# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../minilibx-linux/mlx.h"
# include <X11/cursorfont.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include "../libft/ft_printf/ft_printf.h"
# include <math.h>
# include <fcntl.h>
# include "X11/X.h"
# include "X11/keysym.h"
# include <sys/time.h>

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
# define MOVE_SPEED 0.05
# define MAX_ZOMBIES 32
# define ZOMBIE_SPEED 0.01
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MINIMAP_RADIUS 5                 // Visualizza 11x11 tile
# define MINIMAP_TILE_AREA 11
# define TILE_SIZE 18                     // Dimensione visiva di ogni tile
# define RADAR_RADIUS_PIXELS 92           // Raggio visibile più ampio
# define MINIMAP_CENTER_X 100             // Centro fisso orizzontale
# define MINIMAP_CENTER_Y 100             // Centro fisso verticale (idem)
# define RADAR_COLOR 0x555555             // Colore sfondo radar
# define GRID_COLOR 0x003F00              // Colore della griglia dei tile
# define ZOMBIE_SPEED 0.01
# define MAX_SPRITE_HEIGHT 1000
# define MIN_SPRITE_HEIGHT 100
# define MAX_SPRITE_WIDTH 1000
# define MIN_SPRITE_WIDTH 100

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_draw_data
{
	double	dx;
	double	dy;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		screen_x;
	int		screen_y;
	int		radius;
	int		px;
	int		py;
	double	dist;
	double	step_x;
	double	step_y;
	double	next_x;
	double	next_y;
}	t_draw_data;

typedef struct s_projectile
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	int					damage;
	int					active;
	struct s_projectile	*next;
}	t_projectile;

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

typedef struct s_zombie
{
	double			x;
	double			y;
	int				health;
	int				max_health;
	int				attack_power;
	int				attacked;
	long			last_attack_time;
	struct s_zombie	*next;
	int				sprite_index;
	int				is_dead;
	int				is_walking;
	int				is_attacking;
	int				is_hit;
	int				animation_frame;
	t_tex			*texture;
}	t_zombie;

typedef struct s_gen
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				ignore_next_mouse;
	int				last_mouse_x;
	int				mouse_initialized;
	int				last_mouse_y;
	t_img			img;
	t_player		player;
	t_keys			keys;
	t_map			map;
	t_zombie		*zombies;
	int				num_zombies;
	t_projectile	*projectiles;
	char			player_orientation;
	char			arrow_orientation;
	t_tex			*zombie_tex_walking[26];
	t_tex			*zombie_tex_attacking[17];
	t_tex			*zombie_tex_dead[21];
	t_tex			*zombie_tex_hit[13];
	int				max_health;
	int				health;
	int				ammo;
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
void	update_zombies_position(t_gen *gen);
void	shoot_projectile(t_gen *gen, int x, int y);
void	update_projectile_position(t_gen *gen);
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
void	draw_minimap(t_map *map, t_gen *gen);
int		get_x(t_map *map, char c);
int		get_y(t_map *map, char c, int col);
void	draw_minimap_arrow(t_gen *gen);
void	draw_minimap_grid(t_img *img, t_gen *gen);
void	draw_zombie_column(t_gen *gen, int screen_x, int draw_start,
			int draw_end);
void	add_zombie(t_gen *gen, double x, double y);
void	remove_zombie(t_gen *gen, t_zombie *zombie_to_remove);
void	cleanup_projectiles(t_gen *gen);
void	add_projectile(t_gen *gen);
void	check_zombie_hits(t_gen *gen);
void	init_main(t_gen *gen);
void	load_textures(t_gen *gen);
int		on_key_press(int keycode, t_gen *gen);
int		on_key_release(int keycode, t_gen *gen);
int		on_mouse_move(int x, int y, t_gen *gen);
int		on_mouse_click(int button, int x, int y, t_gen *gen);
void	init_main(t_gen *gen);
void	load_textures(t_gen *gen);
void	draw_zombies(t_gen *gen);
void	draw_projectiles(t_gen *gen);
void	add_zombie(t_gen *gen, double x, double y);
void	remove_zombie(t_gen *gen, t_zombie *zombie_to_remove);
void	move_zombie(t_gen *gen, t_zombie *z, t_draw_data d);
void	update_zombies_position(t_gen *gen);
size_t	get_current_time(void);
void	damage_player(t_zombie *z, t_gen *gen);
int		unclosed_zero(t_map *map);
void	ft_lstclear_proj(t_projectile **stackA);
void	draw_zombie_sprite(t_gen *gen, t_draw_data *d, t_zombie *z);
void	draw_healthbar(t_gen *gen);
void	animate_zombies(t_gen *gen);
void	update_walking(t_zombie *z);
void	update_attacking(t_zombie *z);
void	update_dead(t_zombie *z);
void	update_hit(t_zombie *z);
void	draw_zombie_dots(t_gen *gen);

#endif