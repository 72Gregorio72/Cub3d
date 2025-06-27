/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:28:29 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/24 17:28:29 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	game_loop(t_gen *gen)
{
	if (gen->keys.left)
		rotate_player(gen, -ROTATE_SPEED);
	if (gen->keys.right)
		rotate_player(gen, ROTATE_SPEED);
	clear_image(&gen->img);
	raycasting(gen);
	check_movements(gen);
	update_projectile_position(gen);
	check_zombie_hits(gen);
	cleanup_projectiles(gen);
	update_zombies_position(gen);
	draw_healthbar(gen);
	animate_zombies(gen);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_gen	gen;

	if (!pre_checks(ac, av, &gen))
		return (0);
	init_main(&gen);
	if (!read_map(av, &gen))
		return (0);
	if (!parsing_map(&gen))
		return (free_gen(&gen, 1), 0);
	gen.mlx_ptr = mlx_init();
	gen.win_ptr = mlx_new_window(gen.mlx_ptr, SCREEN_X, SCREEN_Y, "cub3D");
	load_textures(&gen);
	rotate_view(&gen);
	mlx_hook(gen.win_ptr, DestroyNotify, StructureNotifyMask,
		&close_window, &gen);
	mlx_hook(gen.win_ptr, KeyPress, KeyPressMask, &on_key_press, &gen);
	mlx_hook(gen.win_ptr, KeyRelease, KeyReleaseMask, &on_key_release, &gen);
	mlx_mouse_hook(gen.win_ptr, &on_mouse_click, &gen);
	mlx_hook(gen.win_ptr, MotionNotify, PointerMotionMask,
		&on_mouse_move, &gen);
	mlx_loop_hook(gen.mlx_ptr, game_loop, &gen);
	mlx_loop(gen.mlx_ptr);
	return (0);
}

/*printf(GREEN"Map loaded successfully!\n"RESET);
printf("Map dimensions: %d x %d\n", gen.map.width, gen.map.height);*/