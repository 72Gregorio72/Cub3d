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
# include <time.h>
# include <dirent.h>

# define MAPS_PER_ROW 3
# define MAP_BOX_W 250
# define MAP_BOX_H 50
# define START_X 100
# define START_Y 150
# define SCREEN_X 1920
# define SCREEN_Y 1080
# define KB_W 119
# define KB_S 115
# define KB_A 97
# define KB_D 100
# define KB_E 101
# define KB_Q 113
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
# define MOUSE_LEFT_RELEASE 2
# define MOUSE_RIGHT_CLICK 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define MINIMAP_RADIUS 5
# define MINIMAP_TILE_AREA 11
# define TILE_SIZE 18
# define RADAR_RADIUS_PIXELS 92
# define MINIMAP_CENTER_X 100
# define MINIMAP_CENTER_Y 100
# define RADAR_COLOR 0x555555
# define GRID_COLOR 0x003F00
# define ZOMBIE_SPEED 0.01
# define MAX_SPRITE_HEIGHT 1000
# define MIN_SPRITE_HEIGHT 100
# define MAX_SPRITE_WIDTH 1000
# define MIN_SPRITE_WIDTH 100
# define MOUSE_SENSITIVITY 0.5
# define MAX_MAPS 100
# define PREVIEW_WIDTH  200
# define PREVIEW_HEIGHT 200
# define PREVIEW_MARGIN_Y 80

typedef struct s_gen	t_gen;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_draw_data
{
	double			dx;
	double			dy;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				screen_x;
	int				screen_y;
	int				radius;
	int				px;
	int				py;
	double			dist;
	double			step_x;
	double			step_y;
	double			next_x;
	double			next_y;
	int				sprite_height;
	int				sprite_width;
	unsigned int	color;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				x;
	int				tex_x;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}	t_draw_data;

typedef struct s_menu_data
{
	int	i;
	int	j;
	int	radius;
	int	cx;
	int	cy;
	int	dx;
	int	dy;
	int	color;
	int	text_area_color;
	int	x;
	int	y;
}	t_menu_data;

typedef struct s_map_preview
{
	int	map_w;
	int	map_h;
	int	preview_cx;
	int	preview_cy;
	int	max_dim;
	int	cube_size;
	int	center_offset_x;
	int	center_offset_y;
	int	base_x;
	int	base_y;
	int	i;
	int	j;
	int	y;
	int	x;
	int	iso_x;
	int	iso_y;
	int	color;
}	t_map_preview;

typedef struct s_menu_button
{
	int			x1;
	int			y1;
	int			x0;
	int			y0;
	void		(*action)(t_gen *gen);
}	t_menu_button;

typedef struct s_map_button
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	char	*text;
	void	(*action)(t_gen *gen);
	char	*filepath;
}	t_map_button;

typedef struct s_option_data
{
	int				i;
	int				y;
	int				bx1;
	int				by1;
	int				bx2;
	int				by2;
	char			*key_name;
	char			*tmp;
	char			*buf;
	char			*keys[4];
	int				*bindings[4];
	int				color;
	int				x;
	int				y2;
	int				padding;
	int				button_w;
	int				button_h;
}	t_option_data;

typedef struct s_map_selector
{
	int				i;
	int				count;
	char			**map_files;
	int				base_x[3];
	int				col;
	int				row;
	int				x;
	int				y;
	int				offset_y;
	int				padding_x;
	int				padding_y;
	int				button_w;
	int				button_h;
	t_menu_button	x_btn;
	int				text_x;
	int				text_y;
	int				j;
}	t_map_selector;

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

typedef struct s_door
{
	t_tex		door_closed;
	t_tex		door_half_open;
	t_tex		door_open;
	double		dist_player;
	int			flag_door_open;
}				t_door;

typedef struct player_options
{
	float	mouse_sensitivity;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
}	t_player_options;

typedef struct s_key_button
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			*key;
	const char	*label;
}	t_key_button;

typedef struct s_gen
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					ignore_next_mouse;
	int					last_mouse_x;
	int					mouse_initialized;
	int					last_mouse_y;
	t_img				img;
	t_player			player;
	t_keys				keys;
	t_map				map;
	t_zombie			*zombies;
	int					num_zombies;
	t_projectile		*projectiles;
	char				player_orientation;
	char				arrow_orientation;
	t_tex				*zombie_tex_walking[26];
	t_tex				*zombie_tex_attacking[17];
	t_tex				*zombie_tex_dead[21];
	t_tex				*zombie_tex_hit[13];
	t_door				door;
	int					max_health;
	int					health;
	int					ammo;
	int					mouse_vertical_offset;
	double				zbuffer[SCREEN_X];
	int					in_menu;
	t_map_button		*map_buttons;
	t_menu_button		menu_buttons[4];
	int					map_button_count;
	int					scroll_offset_y;
	t_tex				btn_options;
	t_tex				btn_start_game;
	t_tex				btn_map_selection;
	t_tex				btn_exit_game;
	t_tex				btn_back_home;
	t_tex				title_tex;
	char				*map_file_path;
	int					counter_spawn;
	int					map_selection;
	t_player_options	player_options;
	int					in_options;
	int					waiting_key_for;
	t_key_button		key_buttons[4];
	int					selected_key_index;
	int					dragging_slider;
	t_key_button		dragging_slider_button;
	int					is_initializing;
	t_map_selector		x_btn_container[2];
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
	char	hit_tile;
	double	wall_x;
}				t_ray;

//init
void	init_image(t_gen *gen);
void	init_main(t_gen *gen);

//free and clear
void	clean_path(char *path);
void	free_gen(t_gen *gen, int flag);
void	clear_image(t_img *img);
int		close_window(t_gen *gen);
void	clear_image(t_img *img);
void	free_matrix(char **matrix, int height);
void	destroy_zombie_tex(t_gen *gen);
void	free_gpicchio_matrix(char **matrix);
void	free_all_buttons(t_gen *gen);

//key listener
int		on_key_press(int keycode, t_gen *gen);
int		on_key_release(int keycode, t_gen *gen);
int		on_mouse_move(int x, int y, t_gen *gen);
int		on_mouse_click(int button, int x, int y, t_gen *gen);
int		on_key_press(int keycode, t_gen *gen);
int		on_key_release(int keycode, t_gen *gen);
void	mouse_check(int x, int y, t_gen *gen);
void	handle_menu_click(int x, int y, t_gen *gen);
void	handle_options_click(int x, int y, t_gen *gen);
void	handle_scroll(int button, t_gen *gen);

//load map
void	read_file(int fd, int i, t_gen *gen, int y);
int		read_map(char **av, t_gen *gen);
void	get_map_dimensions(char *file, t_map *map);
void	fill_map_row(t_gen *gen, char *line, int y);

//parsing
int		unclosed_zero(t_map *map);
int		unclosed_door(t_map *map);
int		check_closed(t_gen *gen);
int		pre_checks(int ac, char **av, t_gen *gen);
int		parsing_map(t_gen *gen);
int		map_check(t_gen *gen);

//raycasting
void	raycasting(t_gen *gen);
void	calculate_distance(t_ray *ray, t_gen *gen);
void	check_hit(t_ray *ray, t_gen *gen);
void	init_ray(t_ray *ray, t_gen *gen);
void	get_step(t_ray *ray, t_gen *gen);
t_tex	*select_texture(t_ray *ray, t_gen *gen);
void	clear_image(t_img *img);
int		pre_checks(int ac, char **av, t_gen *gen);
void	clean_path(char *path);
void	load_texture(void *mlx, char *path, t_tex *tex);
void	init_image(t_gen *gen);
void	rotate_player(t_gen *gen, double angle);
int		is_walkable(t_gen *gen, double x, double y);
void	check_movements_util(t_gen *gen);
void	check_movements(t_gen *gen);
int		is_walkable(t_gen *gen, double x, double y);
void	put_pixel(t_img *img, int x, int y, int color);

//textures
void	load_textures(t_gen *gen);
void	load_texture(void *mlx, char *path, t_tex *tex);
t_tex	*select_texture(t_ray *ray, t_gen *gen);
int		get_texture_paths(char *file, t_gen *gen);
void	load_texture(void *mlx, char *path, t_tex *tex);

//player
void	damage_player(t_zombie *z, t_gen *gen);
void	update_player_position(int keysym, t_gen *gen);
void	rotate_player(t_gen *gen, double angle);
void	set_player_position(t_gen *gen);

//drawing
void	draw_texture_column(t_ray *ray, t_gen *gen, t_tex *tex, int tex_x);
void	draw_ceiling_and_floor(t_ray *ray, t_gen *gen);
void	draw_doors(t_gen *gen, t_ray *ray);
void	draw_healthbar(t_gen *gen);
void	draw_minimap_arrow(t_gen *gen);
void	draw_minimap_grid(t_img *img, t_gen *gen);
void	draw_minimap(t_map *map, t_gen *gen);

// projectile
void	update_projectile_position(t_gen *gen);
void	ft_lstclear_proj(t_projectile **stackA);
void	draw_projectiles(t_gen *gen);
void	cleanup_projectiles(t_gen *gen);
void	add_projectile(t_gen *gen);
void	util_calculate_prog(t_draw_data d, t_gen *gen, int x, int y);
int		check_proj_hit(t_gen *gen, t_projectile *p, t_zombie *z, t_draw_data d);

// zombie
void	update_hit(t_zombie *z);
void	update_dead(t_zombie *z);
void	update_attacking(t_zombie *z);
void	update_zombies_position(t_gen *gen);
void	draw_zombie_column(t_gen *gen, int screen_x, int draw_start,
			int draw_end);
void	add_zombie(t_gen *gen, double x, double y);
void	remove_zombie(t_gen *gen, t_zombie *zombie_to_remove);
void	check_zombie_hits(t_gen *gen);
void	draw_zombies(t_gen *gen);
void	add_zombie(t_gen *gen, double x, double y);
void	remove_zombie(t_gen *gen, t_zombie *zombie_to_remove);
void	move_zombie(t_gen *gen, t_zombie *z, t_draw_data d);
void	update_zombies_position(t_gen *gen);
void	animate_zombies(t_gen *gen);
void	draw_zombie_sprite(t_gen *gen, t_draw_data *d, t_zombie *z);
void	draw_zombie_dots(t_gen *gen);
void	load_zombie(t_gen *gen, int i, int j);
void	update_walking(t_zombie *z);
void	update_attacking(t_zombie *z);
void	update_dead(t_zombie *z);
void	update_hit(t_zombie *z);
void	draw_menu(t_gen *gen);
void	start_game_from_map(t_gen *gen, const char *filepath);
void	draw_map_selector(t_gen *gen);
t_tex	*get_texture(char *path, t_gen *gen);
void	load_button_images(t_gen *gen);
void	reset_player(t_gen *gen);
int		get_map(char *path, t_gen *gen);
size_t	get_current_time(void);
void	rotate_view(t_gen *gen);
int		zombie_near_door(t_gen *gen, t_ray *ray);
void	load_zombies(t_gen *gen);
void	reset_zombies(t_gen *gen);
void	update_walking(t_zombie *z);
void	update_attacking(t_zombie *z);
void	update_dead(t_zombie *z);
void	update_hit(t_zombie *z);
void	define_dimensions_zombies(t_draw_data *d);
void	loop_on_y_draw_zombie_sprite(double tex_pos, t_gen *gen,
			t_draw_data *d, t_tex *tex);

// menu
int		get_map(char *path, t_gen *gen);
void	set_preview(t_map_preview *preview,
			t_gen *gen, int preview_origin_x, int preview_origin_y);
void	draw_map_preview(t_gen *gen,
			int preview_origin_x, int preview_origin_y);
void	draw_map_preview(t_gen *gen,
			int preview_origin_x, int preview_origin_y);
void	draw_texture(t_img *img, t_tex *tex, int x0, int y0);
void	start_game_from_map(t_gen *gen, const char *filepath);
void	open_options_menu(t_gen *gen);
void	set_slider(t_gen *gen, int slider_x);
void	draw_slider(t_gen *gen);
void	set_options(t_gen *gen, t_option_data *data);
void	set_option_data(t_option_data *data, t_gen *gen);
void	draw_option(t_option_data *data, t_gen *gen);
char	**get_map_files(int *count);

// buttons
int		update_buttons(t_gen *gen, int x, int y);
void	set_menu_buttons(t_gen *gen);
/*void	draw_button_debug_outline(t_img *img,
			int x0, int y0, int x1, int y1, int color);*/
void	draw_button_with_action(t_gen *gen, t_menu_button *button);
void	start_game(t_gen *gen);
void	open_map_selection(t_gen *gen);
void	back_home_menu(t_gen *gen);
void	exit_game(t_gen *gen);
void	set_button(t_menu_button *button,
			t_draw_data data, void (*action)(t_gen *));
void	set_map_buttons(t_gen *gen);
void	set_x_buttons(t_gen *gen, t_map_selector map, int i);

//utils
void	util_rotate_player(t_gen *gen);
void	load_img(t_gen *gen);
void	util_destroy_zombie_tex(t_gen *gen);
char	*mlx_get_key_name(int keycode);
int		mouse_release(int button, int x, int y, t_gen *gen);
void	draw_slider(t_gen *gen);
int		update_buttons(t_gen *gen, int x, int y);
void	loop_calculate_proj(t_gen *gen, t_draw_data *d, int x, int y);
void	util_close_window(t_gen *gen);

#endif