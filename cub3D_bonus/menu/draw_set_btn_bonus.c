/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_set_btn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:51:00 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/10 15:02:01 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* void	draw_button_debug_outline(t_img *img,
	int x0, int y0, int x1, int y1, int color)
{
	int		x;
	int		y;

	x = x0;
	while (x <= x1)
	{
		put_pixel(img, x, y0, color);
		put_pixel(img, x, y1, color);
		x++;
	}
	y = y0;
	while (y <= y1)
	{
		put_pixel(img, x0, y, color);
		put_pixel(img, x1, y, color);
		y++;
	}
} */

void	draw_button_with_action(t_gen *gen, t_menu_button *button)
{
	t_tex	*tex;
	int		offset_x;
	int		offset_y;

	tex = NULL;
	if (button->action == start_game)
		tex = &gen->btn_start_game;
	else if (button->action == open_map_selection)
		tex = &gen->btn_map_selection;
	else if (button->action == exit_game)
		tex = &gen->btn_exit_game;
	else if (button->action == open_options_menu)
		tex = &gen->btn_options;
	else if (button->action == back_home_menu)
		tex = &gen->btn_back_home;
	else if (button->action == map_editor)
		tex = &gen->btn_start_game;
	offset_x = (button->x1 - button->x0 - tex->width) / 2;
	offset_y = (button->y1 - button->y0 - tex->height) / 2;
	if (tex && tex->img_ptr)
		draw_texture(&gen->img, tex, button->x0
			+ offset_x, button->y0 + offset_y);
}

void	set_menu_buttons(t_gen *gen)
{
	t_draw_data	data;
	int			spacing;

	spacing = 176;
	data.x0 = SCREEN_X - 400 - 100;
	data.y0 = 50;
	data.x1 = SCREEN_X - 400 - 100 + 400;
	data.y1 = data.y0 + 180;
	set_button(&gen->menu_buttons[0], data, start_game);
	data.y0 = data.y1 + spacing;
	data.y1 = data.y0 + 60;
	set_button(&gen->menu_buttons[1], data, open_map_selection);
	data.y0 = data.y1 + spacing;
	data.y1 = data.y0 + 60;
	set_button(&gen->menu_buttons[2], data, open_options_menu);
	data.y0 = data.y1 + spacing;
	data.y1 = data.y0 + 60;
	set_button(&gen->menu_buttons[3], data, exit_game);
	data.x0 = SCREEN_X / 2;
	data.y0 = SCREEN_Y / 2;
	data.x1 = SCREEN_X / 2 + 200;
	data.y1 = data.y0 + 60;
	set_button(&gen->menu_buttons[4], data, map_editor);
}

int	update_buttons(t_gen *gen, int x, int y)
{
	int				i;
	t_key_button	key_btn;

	i = 0;
	while (i < 4)
	{
		key_btn = gen->key_buttons[i];
		if (x >= key_btn.x1 && x <= key_btn.x2
			&& y >= key_btn.y1 && y <= key_btn.y2)
		{
			gen->selected_key_index = i;
			gen->waiting_key_for = i + 1;
			open_options_menu(gen);
			return (0);
		}
		i++;
	}
	return (1);
}
