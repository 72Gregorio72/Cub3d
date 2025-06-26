/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minigame_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:34:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/26 12:41:51 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_zombie(t_gen *gen, t_draw_data draw_data)
{
	if (draw_data.transform_y > 0)
	{
		draw_data.sprite_screen_x = (int)((SCREEN_X / 2)
				* (1 + draw_data.transform_x / draw_data.transform_y));
		draw_data.line_height = abs((int)(SCREEN_Y
					/ draw_data.transform_y));
		draw_data.draw_start = -draw_data.line_height / 2 + SCREEN_Y / 2;
		draw_data.draw_end = draw_data.line_height / 2 + SCREEN_Y / 2;
		if (draw_data.sprite_screen_x >= 0
			&& draw_data.sprite_screen_x < SCREEN_X)
			draw_zombie_column(gen, draw_data.sprite_screen_x,
				draw_data.draw_start, draw_data.draw_end);
	}
}

void	draw_zombies(t_gen *gen)
{
	t_zombie		*z;
	t_draw_data		draw_data;

	z = gen->zombies;
	while (z)
	{
		draw_data.dx = z->x - gen->player.x;
		draw_data.dy = z->y - gen->player.y;
		draw_data.inv_det = 1.0 / (gen->player.plane_x * gen->player.dir_y
				- gen->player.dir_x * gen->player.plane_y);
		draw_data.transform_x = draw_data.inv_det
			* (gen->player.dir_y * draw_data.dx
				- gen->player.dir_x * draw_data.dy);
		draw_data.transform_y = draw_data.inv_det
			* (-gen->player.plane_y * draw_data.dx
				+ gen->player.plane_x * draw_data.dy);
		calculate_zombie(gen, draw_data);
		z = z->next;
	}
}

void	calculate_proj(t_gen *gen, t_draw_data d, int x, int y)
{
	if (d.transform_y > 0.0)
	{
		d.screen_x = (int)((SCREEN_X / 2)
				* (1 + d.transform_x / d.transform_y));
		d.screen_y = (int)(SCREEN_Y / 2 + (d.transform_y * 0));
		d.radius = 10;
		y = -d.radius;
		while (y <= d.radius)
		{
			x = -d.radius;
			while (x <= d.radius)
			{
				if (x * x + y * y <= d.radius * d.radius)
				{
					d.px = d.screen_x + x;
					d.py = d.screen_y + y;
					if (d.px >= 0 && d.px < SCREEN_X
						&& d.py >= 0 && d.py < SCREEN_Y)
						put_pixel(&gen->img, d.px, d.py, 0xFF0000);
				}
				x++;
			}
			y++;
		}
	}
}

void	draw_projectiles(t_gen *gen)
{
	t_projectile	*proj;
	t_draw_data		d;
	int				x;
	int				y;

	x = 0;
	y = 0;
	proj = gen->projectiles;
	while (proj)
	{
		d.dx = proj->x - gen->player.x;
		d.dy = proj->y - gen->player.y;
		d.inv_det = 1.0 / (gen->player.plane_x * gen->player.dir_y
				- gen->player.dir_x * gen->player.plane_y);
		d.transform_x = d.inv_det
			* (gen->player.dir_y * d.dx - gen->player.dir_x * d.dy);
		d.transform_y = d.inv_det
			* (-gen->player.plane_y * d.dx + gen->player.plane_x * d.dy);
		calculate_proj(gen, d, x, y);
		proj = proj->next;
	}
}
