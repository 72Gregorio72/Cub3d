/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_set_btn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:51:00 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/09 13:41:02 by vcastald         ###   ########.fr       */
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

void	draw_button_with_action(t_gen *gen, t_map_button *button)
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
	offset_x = (button->x1 - button->x0 - tex->width) / 2;
	offset_y = (button->y1 - button->y0 - tex->height) / 2;
	if (tex && tex->img_ptr)
		draw_texture(&gen->img, tex, button->x0
			+ offset_x, button->y0 + offset_y);
}

void	set_buttons(t_gen *gen)
{
	int	i;

	i = 0;
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 50,
		SCREEN_X - 400 - 100 + 400, 50 + 180,
		"START", start_game);
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 50 + 180 + 40 + 60,
		SCREEN_X - 400 - 100 + 400, 50 + 2 * 180 + 40 + 60,
		"SELECT", open_map_selection);
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100 + 20,
		50 + 2 * (180 + 40 + 60),
		SCREEN_X - 400 - 100 + 400 - 20,
		50 + 3 * 180 + 2 * (40 + 60) - 10,
		"OPTIONS", open_options_menu);
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 50 + 3 * (180 + 40 + 60),
		SCREEN_X - 400 - 100 + 400, 50 + 4 * 180 + 3 * (40 + 60),
		"QUIT", exit_game);
	while (i < gen->map_button_count)
		draw_button_with_action(gen, &gen->map_buttons[i++]);
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
