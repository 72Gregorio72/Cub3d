/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:10:48 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/26 12:38:18 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_background(t_img *img)
{
	int	x;
	int	y;
	int	radius;

	radius = RADAR_RADIUS_PIXELS;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(img, MINIMAP_CENTER_X + x,
					MINIMAP_CENTER_Y + y, RADAR_COLOR);
			x++;
		}
		y++;
	}
}

void	assign_color_tiles(int *color, t_gen *gen, int i, int j)
{
	int	map_y;
	int	map_x;

	map_y = (int)(gen->player.y + i);
	map_x = (int)(gen->player.x + j);
	if (map_y >= 0 && map_y < gen->map.height
		&& map_x >= 0 && map_x < gen->map.width)
	{
		if (gen->map.map_matrix[map_y][map_x] == '1')
			*color = 0x001F00;
		else if (gen->map.map_matrix[map_y][map_x] == '0'
				|| gen->map.map_matrix[map_y][map_x] == '2')
			*color = 0x005F00;
		else
			*color = 0x005F00;
	}
	else
		*color = 0x001F00;
}

void	draw_tile(t_gen *gen, int i, int j, int color)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			draw_x = MINIMAP_CENTER_X + j * TILE_SIZE + x
				- (int)((gen->player.x - floor(gen->player.x)) * TILE_SIZE);
			draw_y = MINIMAP_CENTER_Y + i * TILE_SIZE + y
				- (int)((gen->player.y - floor(gen->player.y)) * TILE_SIZE);
			if (((draw_x - MINIMAP_CENTER_X) * (draw_x - MINIMAP_CENTER_X))
				+ ((draw_y - MINIMAP_CENTER_Y) * (draw_y - MINIMAP_CENTER_Y))
				<= RADAR_RADIUS_PIXELS * RADAR_RADIUS_PIXELS)
				put_pixel(&gen->img, draw_x, draw_y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_tiles(t_gen *gen)
{
	int			i;
	int			j;
	double		px;
	double		py;
	int			color;

	px = gen->player.x;
	py = gen->player.y;
	i = -MINIMAP_RADIUS;
	while (i <= MINIMAP_RADIUS)
	{
		j = -MINIMAP_RADIUS;
		while (j <= MINIMAP_RADIUS)
		{
			assign_color_tiles(&color, gen, i, j);
			draw_tile(gen, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_map *map, t_gen *gen)
{
	map = &gen->map;
	draw_minimap_background(&gen->img);
	draw_minimap_tiles(gen);
	draw_minimap_grid(&gen->img, gen);
	draw_minimap_arrow(gen);
}
