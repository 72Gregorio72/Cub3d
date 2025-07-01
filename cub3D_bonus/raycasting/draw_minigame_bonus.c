/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minigame_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/01 15:41:29 by vcastald         ###   ########.fr       */
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

void draw_zombie_sprite(t_gen *gen, t_draw_data *d, t_zombie *z)
{
	t_tex *tex; 
	
	tex = z->texture;
	if (!tex || !tex->data)
		return;
	int y, x;
	int tex_x, tex_y;
	double tex_pos;

	int sprite_screen_x = d->sprite_screen_x;
	int sprite_height = d->line_height;
	int sprite_width = sprite_height;

	if (sprite_height > MAX_SPRITE_HEIGHT)
		sprite_height = MAX_SPRITE_HEIGHT;
	else if (sprite_height < MIN_SPRITE_HEIGHT)
		sprite_height = MIN_SPRITE_HEIGHT;

	if (sprite_width > MAX_SPRITE_WIDTH)
		sprite_width = MAX_SPRITE_WIDTH;
	else if (sprite_width < MIN_SPRITE_WIDTH)
		sprite_width = MIN_SPRITE_WIDTH;

	int draw_start_y = fmax(0, d->draw_start);
	int draw_end_y = fmin(SCREEN_Y - 1, d->draw_end);
	int draw_start_x = fmax(0, sprite_screen_x - sprite_width / 2);
	int draw_end_x = fmin(SCREEN_X - 1, sprite_screen_x + sprite_width / 2);

	for (x = draw_start_x; x < draw_end_x; x++)
	{
		tex_x = (int)((double)(x - (sprite_screen_x - sprite_width / 2)) / sprite_width * tex->width);
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= tex->width) tex_x = tex->width - 1;

		tex_pos = (draw_start_y - SCREEN_Y / 2 + sprite_height / 2) * ((double)tex->height / sprite_height);
		for (y = draw_start_y; y < draw_end_y; y++)
		{
			tex_y = (int)tex_pos;
			tex_pos += (double)tex->height / sprite_height;
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= tex->height) tex_y = tex->height - 1;

			unsigned int color = *(unsigned int *)(tex->data + tex_y * tex->line_length + tex_x * (tex->bpp / 8));
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(&gen->img, x, y, color);
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
		util_calculate_prog(d, gen, x, y);
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
