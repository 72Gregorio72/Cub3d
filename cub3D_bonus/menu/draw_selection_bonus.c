/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_selection_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:52:18 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/10 14:16:28 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_x_buttons(t_gen *gen, t_map_selector map, int i)
{
	t_draw_data	data;

	data.x0 = SCREEN_X - map.button_w - map.padding_x;
	data.y0 = map.padding_y;
	data.x1 = SCREEN_X - map.padding_x;
	data.y1 = map.padding_y + map.button_h;
	set_button(&map.x_btn, data, back_home_menu);
	gen->x_btn_container[i].x_btn = map.x_btn;
	draw_button_with_action(gen, &map.x_btn);
}

void	set_map_values(t_map_selector *map, int i, t_gen *gen)
{
	map->base_x[0] = 100;
	map->base_x[1] = 750;
	map->base_x[2] = 1400;
	map->offset_y = gen->scroll_offset_y;
	map->padding_x = 10;
	map->padding_y = 100;
	map->button_w = 300;
	map->button_h = 130;
	map->col = i % 3;
	map->row = i / 3;
	map->x = map->base_x[map->col];
	map->y = 150 + map->row
		* (PREVIEW_HEIGHT + PREVIEW_MARGIN_Y) + map->offset_y;
}

void	draw_map_selector(t_gen *gen)
{
	t_map_selector	map;
	int				i;

	clear_image(&gen->img);
	i = 0;
	map.map_files = get_map_files(&map.count);
	while (i < gen->map_button_count)
	{
		set_map_values(&map, i, gen);
		if (get_map(map.map_files[i], gen))
			draw_map_preview(gen, map.x, map.y);
		gen->map_buttons[i].x0 = map.x;
		gen->map_buttons[i].y0 = map.y;
		gen->map_buttons[i].x1 = map.x + PREVIEW_WIDTH;
		gen->map_buttons[i].y1 = map.y + PREVIEW_HEIGHT;
		i++;
	}
	free_gpicchio_matrix(map.map_files);
	set_x_buttons(gen, map, 0);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2 - 80, 100,
		0xFFFFFF, "Select a map:");
}
