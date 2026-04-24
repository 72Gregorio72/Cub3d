/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:37:28 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/26 13:44:52 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_grid_on_x(int base_x, int base_y, t_img *img)
{
	int	x;
	int	dx_top;
	int	dy_top;
	int	dx_bot;
	int	dy_bot;

	x = 0;
	while (x < TILE_SIZE)
	{
		dx_top = base_x + x - MINIMAP_CENTER_X;
		dy_top = base_y - MINIMAP_CENTER_Y;
		dx_bot = base_x + x - MINIMAP_CENTER_X;
		dy_bot = base_y + TILE_SIZE - 1 - MINIMAP_CENTER_Y;
		if (dx_top * dx_top + dy_top * dy_top
			<= RADAR_RADIUS_PIXELS * RADAR_RADIUS_PIXELS)
			put_pixel(img, base_x + x, base_y, GRID_COLOR);
		if (dx_bot * dx_bot + dy_bot * dy_bot
			<= RADAR_RADIUS_PIXELS * RADAR_RADIUS_PIXELS)
			put_pixel(img, base_x + x, base_y + TILE_SIZE - 1, GRID_COLOR);
		x++;
	}
}

void	draw_grid_on_y(int base_x, int base_y, t_img *img)
{
	int	y;
	int	dx_left;
	int	dy_left;
	int	dx_right;
	int	dy_right;

	y = 0;
	while (y < TILE_SIZE)
	{
		dx_left = base_x - MINIMAP_CENTER_X;
		dy_left = base_y + y - MINIMAP_CENTER_Y;
		dx_right = base_x + TILE_SIZE - 1 - MINIMAP_CENTER_X;
		dy_right = base_y + y - MINIMAP_CENTER_Y;
		if (dx_left * dx_left + dy_left * dy_left
			<= RADAR_RADIUS_PIXELS * RADAR_RADIUS_PIXELS)
			put_pixel(img, base_x, base_y + y, GRID_COLOR);
		if (dx_right * dx_right + dy_right * dy_right
			<= RADAR_RADIUS_PIXELS * RADAR_RADIUS_PIXELS)
			put_pixel(img, base_x + TILE_SIZE - 1, base_y + y, GRID_COLOR);
		y++;
	}
}

void	draw_minimap_grid(t_img *img, t_gen *gen)
{
	int		i;
	int		j;
	int		base_x;
	int		base_y;
	double	frac_x;

	i = -MINIMAP_RADIUS;
	while (i <= MINIMAP_RADIUS)
	{
		j = -MINIMAP_RADIUS;
		while (j <= MINIMAP_RADIUS)
		{
			frac_x = (gen->player.x - floor(gen->player.x));
			base_x = MINIMAP_CENTER_X + j * TILE_SIZE
				- ((int)(frac_x * TILE_SIZE));
			base_y = MINIMAP_CENTER_Y + i * TILE_SIZE
				- ((int)((gen->player.y - floor(gen->player.y)) * TILE_SIZE));
			draw_grid_on_x(base_x, base_y, img);
			draw_grid_on_y(base_x, base_y, img);
			j++;
		}
		i++;
	}
}
