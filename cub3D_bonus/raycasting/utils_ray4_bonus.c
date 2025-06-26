/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray4_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:02:12 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/26 12:42:13 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_view(t_gen *gen)
{
	if (gen->player_orientation == 'E')
		rotate_player(gen, M_PI / 2);
	else if (gen->player_orientation == 'S')
		rotate_player(gen, M_PI);
	else if (gen->player_orientation == 'W')
		rotate_player(gen, 3 * M_PI / 2);
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

void	update_matrix(int old_x, int old_y, t_player *player, t_gen *gen)
{
	int	new_x;
	int	new_y;

	if (old_y >= 0 && old_y < gen->map.height
		&& old_x >= 0 && old_x < gen->map.width)
		gen->map.map_matrix[old_y][old_x] = '0';
	new_x = (int)player->x;
	new_y = (int)player->y;
	if (new_y >= 0 && new_y < gen->map.height
		&& new_x >= 0 && new_x < gen->map.width)
		gen->map.map_matrix[new_y][new_x] = gen->player_orientation;
}

void	check_movements_util_2(t_gen *gen)
{
	double	new_x;
	double	new_y;

	if (gen->keys.s)
	{
		new_x = gen->player.x - gen->player.dir_x * MOVE_SPEED;
		new_y = gen->player.y - gen->player.dir_y * MOVE_SPEED;
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
	int		old_x;
	int		old_y;

	old_x = (int)gen->player.x;
	old_y = (int)gen->player.y;
	if (gen->keys.w)
	{
		new_x = gen->player.x + gen->player.dir_x * MOVE_SPEED;
		new_y = gen->player.y + gen->player.dir_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
	check_movements_util_2(gen);
	check_movements_util(gen);
	if (old_x != (int)gen->player.x || old_y != (int)gen->player.y)
		update_matrix(old_x, old_y, &gen->player, gen);
}
