/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:01 by marvin            #+#    #+#             */
/*   Updated: 2025/06/20 16:12:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shoot_projectile(t_gen *gen, int x, int y)
{
	(void)x;
	(void)y;
	if (gen->projectiles.active)
		return ;
	gen->projectiles.x = gen->player.x;
	gen->projectiles.y = gen->player.y;
	gen->projectiles.dir_x = gen->player.dir_x;
	gen->projectiles.dir_y = gen->player.dir_y;
	gen->projectiles.damage = 20;
}

void	update_projectile_position(t_gen *gen)
{
	if (!gen->projectiles.active)
		return ;
	double next_x = gen->projectiles.x + gen->projectiles.dir_x * MOVE_SPEED;
	double next_y = gen->projectiles.y + gen->projectiles.dir_y * MOVE_SPEED;

	if (gen->map.map_matrix[(int)next_y][(int)next_x] == '1')
		gen->projectiles.active = 0;
	else
	{
		gen->projectiles.x = next_x;
		gen->projectiles.y = next_y;
		int screen_x = SCREEN_X / 2;
		int screen_y = SCREEN_Y / 2;
		put_pixel(&gen->img, screen_x, screen_y, 0xFF0000);
	}
}