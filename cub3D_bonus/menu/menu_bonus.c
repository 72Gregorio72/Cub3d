/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:52:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/09 10:16:08 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// void draw_map_preview_scaled(t_gen *gen,
//int base_x, int base_y, int width, int height, int cube_size)
// {
// 	int i, j, x, y;
// 	int iso_x, iso_y;
// 	int color;
// 	int top_offset = cube_size / 2;

// 	i = 0;
// 	while (i < height && i < gen->map.height)
// 	{
// 		j = 0;
// 		while (j < width && j < gen->map.width)
// 		{
// 			if (gen->map.map_matrix[i][j] == '1')
// 			{
// 				iso_x = base_x + (j - i) * cube_size;
// 				iso_y = base_y + (j + i) * cube_size / 2;

// 				y = 0;
// 				while (y < cube_size)
// 				{
// 					x = 0;
// 					while (x < cube_size)
// 					{
// 						color = (x == 0 || y == 0
//|| x == cube_size - 1 || y == cube_size - 1) ? 0x000000 : 0xCCCCCC;
// 						put_pixel(&gen->img, iso_x + x, iso_y + y, color);
// 						x++;
// 					}
// 					y++;
// 				}
// 				y = 0;
// 				while (y < top_offset)
// 				{
// 					x = 0;
// 					while (x < cube_size)
// 					{
// 						color = (x == 0 || y == 0
//|| x == cube_size - 1 || y == top_offset - 1) ? 0x000000 : 0xEEEEEE;
// 						put_pixel(&gen->img, iso_x + x, iso_y - y, color);
// 						x++;
// 					}
// 					y++;
// 				}
// 			}
// 			if (gen->map.map_matrix[i][j] == 'N'
// 				|| gen->map.map_matrix[i][j] == 'S'
// 				|| gen->map.map_matrix[i][j] == 'E'
// 				|| gen->map.map_matrix[i][j] == 'W')
// 			{
// 				iso_x = base_x + (j - i) * cube_size;
// 				iso_y = base_y + (j + i) * cube_size / 2;
// 				y = 0;
// 				while (y < cube_size)
// 				{
// 					x = 0;
// 					while (x < cube_size)
// 					{
// 						put_pixel(&gen->img, iso_x + x, iso_y + y, 0xff0000);
// 						x++;
// 					}
// 					y++;
// 				}make 
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	open_options_menu(t_gen *gen)
{
	t_option_data	data;

	set_option_data(&data, gen);
	data.i = 0;
	while (data.i < 4)
	{
		set_options(gen, &data);
		draw_option(&data, gen);
		data.i++;
	}
	set_button(&data.btn,
		SCREEN_X - data.button_w - data.padding,
		data.padding,
		SCREEN_X - data.padding,
		data.padding + data.button_h,
		"", back_home_menu);
	draw_button_with_action(gen, &data.btn);
	gen->map_button_count = 1;
	gen->map_buttons[3] = data.btn;
	gen->selected_key_index = -1;
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
}

void	free_buttons(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->map_button_count)
	{
		if (gen->map_buttons[i].filepath)
			free(gen->map_buttons[i].filepath);
		i++;
	}
}

void	draw_menu(t_gen *gen)
{
	int	title_x;

	title_x = (SCREEN_X - ft_strlen("CUB3D") * 20) / 2;
	free_buttons(gen);
	gen->map_selection = 0;
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
	gen->map_button_count = 0;
	set_buttons(gen);
	draw_texture(&gen->img, &gen->title_tex,
		SCREEN_X / 2 - gen->title_tex.width / 2, -20);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
}
