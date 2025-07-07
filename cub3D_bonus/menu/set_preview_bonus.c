/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_preview_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:46:24 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/07 15:46:47 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	if_checks(int i, int j, int radius, int *cx, int *cy)
{
	if (j < radius)
		*cx = radius;
	else if (j >= PREVIEW_WIDTH - radius)
		*cx = PREVIEW_WIDTH - radius - 1;
	else
		*cx = j;
	if (i < radius)
		*cy = radius;
	else if (i >= PREVIEW_HEIGHT - radius)
		*cy = PREVIEW_HEIGHT - radius - 1;
	else
		*cy = i;
}

void	draw_square(t_gen *gen, t_menu_data *data)
{
	data->dx = data->j - data->cx;
	data->dy = data->i - data->cy;
	if (data->dx * data->dx + data->dy * data->dy
		<= data->radius * data->radius)
	{
		if (data->i < PREVIEW_HEIGHT / 5)
			put_pixel(&gen->img, data->x + data->j,
				data->y + data->i, data->text_area_color);
		else
			put_pixel(&gen->img, data->x + data->j,
				data->y + data->i, data->color);
	}
}

void	draw_width(t_gen *gen, int x, int y, int i)
{
	t_menu_data	data;

	data.text_area_color = 0xFFFFFF;
	data.radius = 12;
	data.color = 0x383838;
	data.j = 0;
	data.i = i;
	data.x = x;
	data.y = y;
	while (data.j < PREVIEW_WIDTH)
	{
		if_checks(data.i, data.j, data.radius, &data.cx, &data.cy);
		draw_square(gen, &data);
		data.j++;
	}
}

void	draw_rounded_background(t_gen *gen, int x, int y)
{
	int	i;

	i = 0;
	while (i < PREVIEW_HEIGHT)
	{
		draw_width(gen, x, y, i);
		i++;
	}
}

void	set_preview(t_map_preview *preview,
	t_gen *gen, int preview_origin_x, int preview_origin_y)
{
	preview->map_w = gen->map.width;
	preview->map_h = gen->map.height;
	preview->preview_cx = preview_origin_x + PREVIEW_WIDTH / 2;
	preview->preview_cy = preview_origin_y + PREVIEW_HEIGHT / 2;
	preview->max_dim = preview->map_w + preview->map_h;
	preview->cube_size = PREVIEW_WIDTH / preview->max_dim;
	preview->center_offset_x = (preview->map_w - preview->map_h)
		* preview->cube_size / 2;
	preview->center_offset_y = (preview->map_w + preview->map_h)
		* preview->cube_size / 4;
	preview->base_x = preview->preview_cx - preview->center_offset_x;
	preview->base_y = preview->preview_cy - preview->center_offset_y;
	draw_rounded_background(gen, preview_origin_x, preview_origin_y);
}
