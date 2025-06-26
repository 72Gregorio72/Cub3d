/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_arrow_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:34:24 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/26 12:37:18 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_inside_triangle(int px, int py, t_point a[3])
{
	float	denom;
	float	b;
	float	c;
	float	alpha;

	denom = ((a[1].y - a[2].y) * (a[0].x - a[2].x)
			+ (a[2].x - a[1].x) * (a[0].y - a[2].y));
	if (denom == 0.0f)
		return (0);
	b = ((a[2].y - a[0].y) * (px - a[2].x)
			+ (a[0].x - a[2].x) * (py - a[2].y)) / denom;
	c = ((a[1].y - a[2].y) * (px - a[2].x)
			+ (a[2].x - a[1].x) * (py - a[2].y)) / denom;
	alpha = 1.0f - b - c;
	return (b >= 0 && c >= 0 && alpha >= 0 && b <= 1 && c <= 1 && alpha <= 1);
}

void	draw_filled_triangle(t_img *img, t_point a[3], int color)
{
	int		px;
	int		py;
	int		min_x;
	int		max_x;
	int		min_y;

	min_x = fmin(a[0].x, fmin(a[1].x, a[2].x));
	max_x = fmax(a[0].x, fmax(a[1].x, a[2].x));
	min_y = fmin(a[0].y, fmin(a[1].y, a[2].y));
	py = min_y;
	while (py <= fmax(a[0].y, fmax(a[1].y, a[2].y)))
	{
		px = min_x;
		while (px <= max_x)
		{
			if (is_inside_triangle(px, py, a))
				put_pixel(img, px, py, color);
			px++;
		}
		py++;
	}
}

void	draw_minimap_arrow(t_gen *gen)
{
	t_point	arrow[3];
	double	angle;
	double	cos_a;
	double	sin_a;

	angle = atan2(gen->player.dir_y, gen->player.dir_x);
	sin_a = sin(angle);
	cos_a = cos(angle);
	arrow[0].x = MINIMAP_CENTER_X + cos_a * 6;
	arrow[0].y = MINIMAP_CENTER_Y + sin_a * 6;
	arrow[1].x = MINIMAP_CENTER_X - cos_a * 6 - sin_a * 4;
	arrow[1].y = MINIMAP_CENTER_Y - sin_a * 6 + cos_a * 4;
	arrow[2].x = MINIMAP_CENTER_X - cos_a * 6 + sin_a * 4;
	arrow[2].y = MINIMAP_CENTER_Y - sin_a * 6 - cos_a * 4;
	draw_filled_triangle(&gen->img, arrow, 0xFF0000);
}
