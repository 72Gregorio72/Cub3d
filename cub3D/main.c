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
	if (!read_map(av, &gen))
		return (0);
	if (!parsing_map(&gen))
		return (free_gen(&gen, 1), 0);
	gen.mlx_ptr = mlx_init();
	gen.win_ptr = mlx_new_window(gen.mlx_ptr, SCREEN_X, SCREEN_Y, "cub3D");
	gen.keys = (t_keys){0, 0, 0, 0, 0, 0};
	init_image(&gen);
	load_texture(gen.mlx_ptr, gen.map.n_tex, &gen.map.north);
	load_texture(gen.mlx_ptr, gen.map.s_tex, &gen.map.south);
	load_texture(gen.mlx_ptr, gen.map.e_tex, &gen.map.east);
	load_texture(gen.mlx_ptr, gen.map.w_tex, &gen.map.west);
	mlx_hook(gen.win_ptr, DestroyNotify, StructureNotifyMask,
		&close_window, &gen);
	mlx_hook(gen.win_ptr, KeyPress, KeyPressMask, &on_key_press, &gen);
	mlx_hook(gen.win_ptr, KeyRelease, KeyReleaseMask, &on_key_release, &gen);
	rotate_view(&gen);
	mlx_loop_hook(gen.mlx_ptr, game_loop, &gen);
	mlx_loop(gen.mlx_ptr);
	return (0);
}

/*printf(GREEN"Map loaded successfully!\n"RESET);
printf("Map dimensions: %d x %d\n", gen.map.width, gen.map.height);*/