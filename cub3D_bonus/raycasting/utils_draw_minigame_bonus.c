/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw_minigame_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/04 12:03:10 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	util_calculate_prog(t_draw_data d, t_gen *gen, int x, int y)
{
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

void	loop_calculate_proj(t_gen *gen, t_draw_data *d, int x, int y)
{
	y = -d->radius;
	while (y <= d->radius)
	{
		x = -d->radius;
		while (x <= d->radius)
		{
			if (x * x + y * y <= d->radius * d->radius)
			{
				d->px = d->screen_x + x;
				d->py = d->screen_y + y;
				if (d->px >= 0 && d->px < SCREEN_X
					&& d->py >= 0 && d->py < SCREEN_Y
					&& d->transform_y < gen->zbuffer[d->px])
				{
					put_pixel(&gen->img, d->px, d->py, 0xFF0000);
				}
			}
			x++;
		}
		y++;
	}	
}

void	define_dimensions_zombies(t_draw_data *d)
{
	d->sprite_height = d->line_height;
	d->sprite_width = d->sprite_height;
	if (d->sprite_height > MAX_SPRITE_HEIGHT)
		d->sprite_height = MAX_SPRITE_HEIGHT;
	else if (d->sprite_height < MIN_SPRITE_HEIGHT)
		d->sprite_height = MIN_SPRITE_HEIGHT;
	if (d->sprite_height > MAX_SPRITE_HEIGHT)
		d->sprite_height = MAX_SPRITE_HEIGHT;
	else if (d->sprite_height < MIN_SPRITE_HEIGHT)
		d->sprite_height = MIN_SPRITE_HEIGHT;
	if (d->sprite_width > MAX_SPRITE_WIDTH)
		d->sprite_width = MAX_SPRITE_WIDTH;
	else if (d->sprite_width < MIN_SPRITE_WIDTH)
		d->sprite_width = MIN_SPRITE_WIDTH;
	if (d->sprite_width > MAX_SPRITE_WIDTH)
		d->sprite_width = MAX_SPRITE_WIDTH;
	else if (d->sprite_width < MIN_SPRITE_WIDTH)
		d->sprite_width = MIN_SPRITE_WIDTH;
	d->draw_start_y = fmax(0, d->draw_start);
	d->draw_end_y = fmin(SCREEN_Y - 1, d->draw_end);
	d->draw_start_x = fmax(0, d->sprite_screen_x - d->sprite_width / 2);
	d->draw_end_x = fmin(SCREEN_X - 1, d->sprite_screen_x + d->sprite_width / 2);
}

void	loop_on_y_draw_zombie_sprite(double tex_pos, t_gen *gen,
	t_draw_data *d, t_tex *tex)
{
	int	y;
	int	tex_y;

	y = d->draw_start_y;
	while (y < d->draw_end_y)
	{
		tex_y = (int)tex_pos;
		tex_pos += (double)tex->height / d->sprite_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		d->color = *(unsigned int *)(tex->data + tex_y * tex->line_length
			+ d->tex_x * (tex->bpp / 8));
		if ((d->color & 0x00FFFFFF) != 0x000000)
			put_pixel(&gen->img, d->x, y, d->color);
		y++;
	}
}
