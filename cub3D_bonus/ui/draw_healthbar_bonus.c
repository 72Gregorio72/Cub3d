/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_healthbar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:29:53 by gpicchio          #+#    #+#             */
/*   Updated: 2025/08/05 13:02:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_healthbar(t_gen *gen)
{
	int	health_bar_width;
	int	health_bar_height;
	int	health_percentage;
	int	i;
	int	j;

	health_bar_width = 200;
	health_bar_height = 30;
	health_percentage = (gen->health * 100) / gen->max_health;
	i = -1;
	while (++i < health_bar_height)
	{
		j = -1;
		while (++j < health_bar_width)
			put_pixel(&gen->img,
				SCREEN_X - health_bar_width - 20 + j, 20 + i, 0x000000);
	}
	i = -1;
	while (++i < health_bar_height)
	{
		j = -1;
		while (++j < (health_bar_width * health_percentage / 100))
			put_pixel(&gen->img,
				SCREEN_X - health_bar_width - 20 + j, 20 + i, 0x00FF00);
	}
}

void	draw_texture_scaled(t_img *img, t_tex *tex, int x0, int y0, float scale)
{
	int				y;
	int				x;
	int				src_y;
	int				src_x;
	char			*pixel;
	unsigned int	color;

	y = 0;
	while (y < (int)(tex->height * scale))
	{
		x = 0;
		while (x < (int)(tex->width * scale))
		{
			src_y = (int)(y / scale);
			src_x = (int)(x / scale);
			pixel = tex->data + (src_y * tex->line_length + src_x * (tex->bpp / 8));
			color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	draw_gun(t_gen *gen)
{
	int gun_x, gun_y;

	gun_x = SCREEN_X - (gen->gun_tex[1]->width * 1.4) + 100;
	gun_y = SCREEN_Y - gen->gun_tex[1]->height * 1.4;
	draw_texture_scaled(&gen->img, gen->gun_tex[1], gun_x, gun_y, 1.4f);
	if (gen->is_shooting)
	{
		draw_texture_scaled(&gen->img, gen->gun_tex[gen->gun_index], gun_x, gun_y, 1.4f);
		gen->gun_index++;
		if (gen->gun_index >= 4)
			gen->gun_index = 0;
	}
}
