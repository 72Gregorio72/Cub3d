/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:52:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 15:25:15 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	open_options_menu(t_gen *gen)
{
	t_option_data	data;
	t_map_selector	map;

	map.padding_x = 200;
	map.padding_y = 200;
	map.button_w = 100;
	map.button_h = 50;
	gen->in_options = 1;
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	set_option_data(&data, gen);
	data.i = 0;
	while (data.i < 4)
	{
		set_options(gen, &data);
		draw_option(&data, gen);
		data.i++;
	}
	set_x_buttons(gen, map, 1);
	gen->selected_key_index = -1;
}

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
	map->i = 0;
}

void	set_map_buttons(t_gen *gen)
{
	t_map_selector	map;

	set_map_preview(gen, &map);
	gen->map_buttons = malloc(sizeof(t_map_button) * map.count);
	gen->map_button_count = map.count;
	while (map.i < map.count && map.i < MAX_MAPS)
	{
		map.col = map.i % 3;
		map.row = map.i / 3;
		map.x = map.base_x[map.col];
		map.y = 150 + map.row;
		free(gen->map_file_path);
		gen->map_file_path = ft_strdup(map.map_files[map.i]);
		gen->map_buttons[map.i] = (t_map_button){
			.x0 = map.x,
			.y0 = map.y,
			.x1 = map.x + PREVIEW_WIDTH,
			.y1 = map.y + PREVIEW_HEIGHT,
			.action = NULL,
			.filepath = ft_strdup(map.map_files[map.i])
		};
		map.i++;
	}
	free_gpicchio_matrix(map.map_files);
}

void	draw_menu(t_gen *gen)
{
	int	title_x;
	int	i;

	i = 0;
	title_x = (SCREEN_X - ft_strlen("CUB3D") * 20) / 2;
	gen->map_selection = 0;
	gen->in_options = 0;
	gen->in_map_editor = 0;
	gen->in_menu = 1;
	clear_image(&gen->img);
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, title_x, 80, 0xFFFFFF, "CUB3D");
	if (gen->map.map_matrix && gen->map.width > 0 && gen->map.height > 0)
	{
		draw_map_preview(gen, 100, 150);
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			500, 300 - 30, 0xFFFFFF, "MAPPA");
	}
	while (i < 5)
	{
		draw_button_with_action(gen, &gen->menu_buttons[i]);
		i++;
	}
	draw_texture(&gen->img, &gen->title_tex,
		SCREEN_X / 2 - gen->title_tex.width / 2, -20);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
}
