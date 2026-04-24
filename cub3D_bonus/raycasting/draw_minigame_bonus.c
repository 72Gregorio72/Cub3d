/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minigame_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:34:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/09 10:06:24 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_zombie(t_gen *gen, t_draw_data draw_data, t_zombie *z)
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
			draw_zombie_sprite(gen, &draw_data, z);
	}
}

void	draw_zombie_sprite(t_gen *gen, t_draw_data *d, t_zombie *z)
{
	t_tex			*tex;
	double			tex_pos;

	tex = z->texture;
	if (!tex || !tex->data)
		return ;
	define_dimensions_zombies(d);
	d->x = d->draw_start_x - 1;
	while (++d->x < d->draw_end_x)
	{
		d->tex_x = (int)((double)(d->x
					- (d->sprite_screen_x - d->sprite_width / 2))
				/ d->sprite_width * tex->width);
		if (d->tex_x < 0)
			d->tex_x = 0;
		if (d->tex_x >= tex->width)
			d->tex_x = tex->width - 1;
		if (d->transform_y > 0 && d->x >= 0 && d->x < SCREEN_X
			&& d->transform_y < gen->zbuffer[d->x])
		{
			tex_pos = (d->draw_start_y - SCREEN_Y / 2 + d->sprite_height / 2)
				* ((double)tex->height / d->sprite_height);
			loop_on_y_draw_zombie_sprite(tex_pos, gen, d, tex);
		}
	}
}

void	draw_zombies(t_gen *gen)
{
	t_zombie			*z;
	t_draw_data			draw_data;

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
		calculate_zombie(gen, draw_data, z);
		z = z->next;
	}
}

void	calculate_proj(t_gen *gen, t_draw_data d, int x, int y)
{
	double	base_radius;
	double	min_radius;
	double	max_radius;
	double	dynamic_radius;

	if (d.transform_y > 0.0)
	{
		d.screen_x = (int)((SCREEN_X / 2)
				* (1 + d.transform_x / d.transform_y));
		d.screen_y = (int)(SCREEN_Y / 2 + (d.transform_y * 0));
		base_radius = 50.0;
		min_radius = 1.0;
		max_radius = 55.0;
		dynamic_radius = base_radius * exp(-d.transform_y / 1.0);
		if (dynamic_radius < min_radius)
			dynamic_radius = min_radius;
		else if (dynamic_radius > max_radius)
			dynamic_radius = max_radius;
		d.radius = (int)dynamic_radius;
		loop_calculate_proj(gen, &d, x, y);
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
