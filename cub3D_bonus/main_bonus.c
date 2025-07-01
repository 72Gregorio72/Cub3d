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

void	load_zombies(t_gen *gen)
{
	int	i;
	int	j;

	gen->zombies = NULL;
	gen->num_zombies = 0;
	i = 0;
	while (i < gen->map.height)
	{
		j = 0;
		while (j < gen->map.width)
		{
			if (gen->map.map_matrix[i][j] == 'Z')
				add_zombie(gen, j + 0.5, i + 0.5);
			j++;
		}
		i++;
	}
}

void	spawn_zombies(t_gen *gen)
{
	static unsigned long	last_spawn_time = 0;
	unsigned long			current_time;
	int						random_h;
	int						random_w;
	int						attempts;

	current_time = get_current_time();
	if (last_spawn_time == 0)
		last_spawn_time = current_time;
	if (current_time - last_spawn_time >= 60000)
	{
		gen->counter_spawn++;
		last_spawn_time = current_time;
	}
	while (gen->counter_spawn > 0)
	{
		attempts = 0;
		do {
			random_h = rand() % gen->map.height;
			random_w = rand() % gen->map.width;
			attempts++;
		} while (gen->map.map_matrix[random_h][random_w] != '0' && attempts < 100);
		if (attempts >= 100)
			return ;
		gen->map.map_matrix[random_h][random_w] = 'Z';
		add_zombie(gen, random_w + 0.5, random_h + 0.5);
		gen->counter_spawn--;
	}
}

int	game_loop(t_gen *gen)
{
	static unsigned long	last_time;
	unsigned long			current_time;

	last_time = 0;
	if (gen->keys.left)
		rotate_player(gen, -ROTATE_SPEED);
	if (gen->keys.right)
		rotate_player(gen, ROTATE_SPEED);
	clear_image(&gen->img);
	spawn_zombies(gen);
	raycasting(gen);
	check_movements(gen);
	update_projectile_position(gen);
	check_zombie_hits(gen);
	cleanup_projectiles(gen);
	update_zombies_position(gen);
	draw_healthbar(gen);
	current_time = get_current_time();
	if (current_time - last_time >= 50)
	{
		animate_zombies(gen);
		last_time = current_time;
	}
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
	load_zombies(&gen);
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
