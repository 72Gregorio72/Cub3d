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
# include "../minilibx-linux/mlx_int.h"
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

typedef struct s_gen
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	t_player	xXpicchio_valePRO2025Xx;
	t_map		map;
}				t_gen;

int		close_window(t_gen *gen);
int		read_map(char **av, t_gen *gen);
void	set_player_position(t_gen *gen);
void	raycasting(t_gen *gen);
int		get_texture_paths(char *file, t_gen *gen);
int		fill_textures(t_gen *gen, char *line, char *original);
void	init_textures(t_gen *gen);
char	*get_path(char *line);
int		map_check(t_gen *gen);
int		parsing_map(t_gen *gen);
void	free_matrix(char **matrix, int height);
void	free_gen(t_gen * gen);
void	print_map(t_gen *gen);
int		get_char_pos(char *src, int c);
int		check_closed(t_gen *gen);
int		map_check(t_gen *gen);

#endif