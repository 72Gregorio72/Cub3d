/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_selection_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:52:18 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/07 15:53:51 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_map_preview(t_gen *gen, t_map_selector *map)
{
	map->base_x[0] = 100;
	map->base_x[1] = 750;
	map->base_x[2] = 1400;
	map->offset_y = gen->scroll_offset_y;
	map->padding_x = 10;
	map->padding_y = 100;
	map->button_w = 300;
	map->button_h = 130;
	clear_image(&gen->img);
	map->map_files = get_map_files(&map->count);
	if (!map->map_files || map->count == 0)
	{
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 50, 50,
			0xFF0000, "No map files found in /maps");
		return ;
	}
	gen->map_button_count = 0;
	map->i = 0;
}

void	draw_map_ui(t_map_selector *map, t_gen *gen)
{
	while (map->i < map->count && map->i < MAX_MAPS)
	{
		map->col = map->i % 3;
		map->row = map->i / 3;
		map->x = map->base_x[map->col];
		map->y = 150 + map->row
			* (PREVIEW_HEIGHT + PREVIEW_MARGIN_Y) + map->offset_y;
		if (get_map(map->map_files[map->i], gen))
			draw_map_preview(gen, map->x, map->y);
		free(gen->map_file_path);
		gen->map_file_path = ft_strdup(map->map_files[map->i]);
		gen->map_buttons[gen->map_button_count++] = (t_map_button){
			.x0 = map->x,
			.y0 = map->y,
			.x1 = map->x + PREVIEW_WIDTH,
			.y1 = map->y + PREVIEW_HEIGHT,
			.text = map->map_files[map->i] + 5,
			.action = NULL,
			.filepath = ft_strdup(map->map_files[map->i]) //// da fare i free
		};
		map->i++;
	}
}

void	write_filename(t_map_selector *map, t_gen *gen)
{
	map->j = 0;
	while (map->j < gen->map_button_count)
	{
		map->text_x = gen->map_buttons[map->j].x0
			+ 100 - ft_strlen(gen->map_buttons[map->j].text) * 4;
		map->text_y = gen->map_buttons[map->j].y0 + 20;
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			map->text_x, map->text_y, 0x000000, gen->map_buttons[map->j].text);
		free(map->map_files[map->j]);
		map->j++;
	}
}

void	draw_map_selector(t_gen *gen)
{
	t_map_selector	map;

	set_map_preview(gen, &map);
	draw_map_ui(&map, gen);
	set_button(&map.button,
		SCREEN_X - map.button_w - map.padding_x,
		map.padding_y,
		SCREEN_X - map.padding_x,
		map.padding_y + map.button_h,
		"", back_home_menu);
	draw_button_with_action(gen, &map.button);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	gen->map_buttons[3] = map.button;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2 - 80, 100,
		0xFFFFFF, "Select a map:");
	write_filename(&map, gen);
	free(map.map_files);
}