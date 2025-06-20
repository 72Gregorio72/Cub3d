/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:31:28 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/19 15:49:27 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pre_checks(int ac, char **av, t_gen *gen)
{
	char	*dot;

	if (ac != 2)
		return (printf(RED"Error: wrong number of arguments!\n"RESET), 0);
	dot = ft_strchr(av[1], '.');
	if (!dot || ft_strncmp(dot, ".cub", 4) || ft_strlen(dot) != 4)
		return (printf(RED"Error: "YELLOW"%s"RED" is not a .cub!\n"RESET, av[1]), 0);
	gen->map.fd_map = open(av[1], O_RDONLY);
	if (gen->map.fd_map == -1)
		return (printf(RED"Error: file not found!\n"RESET), 0);
	return (1);
}

void	clean_path(char *path)
{
	int	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == '\r' || path[len - 1] == ' '))
		path[--len] = '\0';
}

void load_texture(void *mlx, char *path, t_tex *tex)
{
    clean_path(path);
    tex->img_ptr = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img_ptr)
    {
        printf(RED"Failed to load texture: %s\n"RESET, path);
        exit(EXIT_FAILURE);
    }
    tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_length, &tex->endian);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_X || y < 0 || y >= SCREEN_Y)
		return ;
	dst = img->data + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_image(t_gen *gen)
{
	gen->img.img_ptr = mlx_new_image(gen->mlx_ptr, SCREEN_X, SCREEN_Y);
	gen->img.data = mlx_get_data_addr(gen->img.img_ptr,
		&gen->img.bpp, &gen->img.line_length, &gen->img.endian);
	clear_image(&gen->img);
}

void	rotate_player(t_gen *gen, double angle)
{
	double	old_dir_x = gen->player.dir_x;
	double	old_plane_x = gen->player.plane_x;

	gen->player.dir_x = gen->player.dir_x * cos(angle) - gen->player.dir_y * sin(angle);
	gen->player.dir_y = old_dir_x * sin(angle) + gen->player.dir_y * cos(angle);

	gen->player.plane_x = gen->player.plane_x * cos(angle) - gen->player.plane_y * sin(angle);
	gen->player.plane_y = old_plane_x * sin(angle) + gen->player.plane_y * cos(angle);
}

int	is_walkable(t_gen *gen, double x, double y)
{
	int mx = (int)x;
	int my = (int)y;

	return (mx >= 0 && mx < gen->map.width &&
		my >= 0 && my < gen->map.height &&
		gen->map.map_matrix[my][mx] != '1');
}

void	check_movements_util(t_gen *gen)
{
	double	new_x;
	double	new_y;

	if (gen->keys.a)
	{
		new_x = gen->player.x - gen->player.plane_x * MOVE_SPEED;
		new_y = gen->player.y - gen->player.plane_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
	if (gen->keys.d)
	{
		new_x = gen->player.x + gen->player.plane_x * MOVE_SPEED;
		new_y = gen->player.y + gen->player.plane_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
}

void	check_movements(t_gen *gen)
{
	double	new_x;
	double	new_y;

	if (gen->keys.w)
	{
		new_x = gen->player.x + gen->player.dir_x * MOVE_SPEED;
		new_y = gen->player.y + gen->player.dir_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
	if (gen->keys.s)
	{
		new_x = gen->player.x - gen->player.dir_x * MOVE_SPEED;
		new_y = gen->player.y - gen->player.dir_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
	check_movements_util(gen);
}

int	game_loop(t_gen *gen)
{
	check_movements(gen);
	if (gen->keys.left)
		rotate_player(gen, -ROTATE_SPEED);
	if (gen->keys.right)
		rotate_player(gen, ROTATE_SPEED);

	clear_image(&gen->img);
	raycasting(gen);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	return (0);
}

void	update_player_position(int keysym, t_gen *gen)
{
	if (keysym == KB_W)
	{
		gen->player.x += gen->player.dir_x * MOVE_SPEED;
		gen->player.y += gen->player.dir_y * MOVE_SPEED;
	}
	else if (keysym == KB_S)
	{
		gen->player.x -= gen->player.dir_x * MOVE_SPEED;
		gen->player.y -= gen->player.dir_y * MOVE_SPEED;
	}
	else if (keysym == KB_A)
	{
		gen->player.x -= gen->player.plane_x * MOVE_SPEED;
		gen->player.y -= gen->player.plane_y * MOVE_SPEED;
	}
	else if (keysym == KB_D)
	{
		gen->player.x += gen->player.plane_x * MOVE_SPEED;
		gen->player.y += gen->player.plane_y * MOVE_SPEED;
	}
}

int	on_key_press(int keycode, t_gen *gen)
{
	if (keycode == KB_ESC)
	{
		close_window(gen);
		exit(0);
	}
	if (keycode == KB_W)
		gen->keys.w = 1;
	if (keycode == KB_A)
		gen->keys.a = 1;
	if (keycode == KB_S)
		gen->keys.s = 1;
	if (keycode == KB_D)
		gen->keys.d = 1;
	if (keycode == KB_LEFT)
		gen->keys.left = 1;
	if (keycode == KB_RIGHT)
		gen->keys.right = 1;
	return (0);
}

int	on_key_release(int keycode, t_gen *gen)
{
	if (keycode == KB_W)
		gen->keys.w = 0;
	if (keycode == KB_A)
		gen->keys.a = 0;
	if (keycode == KB_S)
		gen->keys.s = 0;
	if (keycode == KB_D)
		gen->keys.d = 0;
	if (keycode == KB_LEFT)
		gen->keys.left = 0;
	if (keycode == KB_RIGHT)
		gen->keys.right = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_gen	gen;

	if (!pre_checks(ac, av, &gen))
		return (0);
	read_map(av, &gen);
	printf(GREEN"Map loaded successfully!\n"RESET);
	printf("Map dimensions: %d x %d\n", gen.map.width, gen.map.height);
	gen.mlx_ptr = mlx_init();
	gen.win_ptr = mlx_new_window(gen.mlx_ptr, SCREEN_X, SCREEN_Y, "cub3D");
	gen.keys = (t_keys){0, 0, 0, 0, 0, 0};
	init_image(&gen);
	load_texture(gen.mlx_ptr, gen.map.N_tex, &gen.map.north);
	load_texture(gen.mlx_ptr, gen.map.S_tex, &gen.map.south);
	load_texture(gen.mlx_ptr, gen.map.E_tex, &gen.map.east);
	load_texture(gen.mlx_ptr, gen.map.W_tex, &gen.map.west);
	mlx_hook(gen.win_ptr, DestroyNotify, StructureNotifyMask, &close_window, &gen);
	mlx_hook(gen.win_ptr, KeyPress, KeyPressMask, &on_key_press, &gen);
	mlx_hook(gen.win_ptr, KeyRelease, KeyReleaseMask, &on_key_release, &gen);
	mlx_loop_hook(gen.mlx_ptr, game_loop, &gen);
	mlx_loop(gen.mlx_ptr);
	return (0);
}
