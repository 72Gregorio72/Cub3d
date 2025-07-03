/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_zombie_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:38:56 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/30 10:40:56 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_single_zombie_dot(t_gen *gen, double rel_x, double rel_y)
{
	int	dx;
	int	dy;
	int	px;
	int	py;

	dy = -11;
	while (++dy <= 10)
	{
		dx = -11;
		while (++dx <= 10)
		{
			px = MINIMAP_CENTER_X + (int)(rel_x * TILE_SIZE) + dx;
			py = MINIMAP_CENTER_Y + (int)(rel_y * TILE_SIZE) + dy;
			if (dx * dx + dy * dy <= 15
				&& ((px - MINIMAP_CENTER_X) * (px - MINIMAP_CENTER_X)
					+ (py - MINIMAP_CENTER_Y) * (py - MINIMAP_CENTER_Y)
					<= RADAR_RADIUS_PIXELS * RADAR_RADIUS_PIXELS))
				put_pixel(&gen->img, px, py, 0xFF00FF);
		}
	}
}

void	draw_zombie_dots(t_gen *gen)
{
	t_zombie	*z;
	double		rel_x;
	double		rel_y;

	z = gen->zombies;
	while (z)
	{
		rel_x = z->x - gen->player.x;
		rel_y = z->y - gen->player.y;
		draw_single_zombie_dot(gen, rel_x, rel_y);
		z = z->next;
	}
}
