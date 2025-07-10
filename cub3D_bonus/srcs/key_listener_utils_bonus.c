/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:36:59 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 14:28:53 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*mlx_get_key_name(int keycode)
{
	static char	s[2] = {0};

	if (keycode >= 'A' && keycode <= 'Z')
	{
		s[0] = keycode;
		return (s);
	}
	if (keycode >= 'a' && keycode <= 'z')
	{
		s[0] = keycode - 32;
		return (s);
	}
	return ("?");
}

int	mouse_release(int button, int x, int y, t_gen *gen)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		if (gen->dragging_slider)
			gen->dragging_slider = 0;
	}
	return (0);
}

void	handle_options_click(int x, int y, t_gen *gen)
{
	if (gen->x_btn_container[1].x_btn.x0 <= x
		&& gen->x_btn_container[1].x_btn.x1 >= x
		&& gen->x_btn_container[1].x_btn.y0 <= y
		&& gen->x_btn_container[1].x_btn.y1 >= y)
	{
		back_home_menu(gen);
		return ;
	}
}

void	handle_menu_click(int x, int y, t_gen *gen)
{
	t_menu_button	btn;
	int				i;

	i = 0;
	while (i < 4)
	{
		btn = gen->menu_buttons[i];
		if (x >= btn.x0 && x <= btn.x1 && y >= btn.y0 && y <= btn.y1)
		{
			btn.action(gen);
			gen->ignore_next_mouse = 1;
		}
		i++;
	}
}

void	handle_scroll(int button, t_gen *gen)
{
	if (button == MOUSE_SCROLL_UP)
	{
		gen->scroll_offset_y += 100;
		draw_map_selector(gen);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		gen->scroll_offset_y -= 100;
		draw_map_selector(gen);
	}
	if (gen->scroll_offset_y > 0)
	{
		gen->scroll_offset_y = 0;
		draw_map_selector(gen);
	}
}

void	handle_map_selection_click(int x, int y, t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->map_button_count)
	{
		draw_button_debug_outline(&gen->img,
			gen->map_buttons[i].x0, gen->map_buttons[i].y0,
			gen->map_buttons[i].x1, gen->map_buttons[i].y1, 0xFFFFFF);
		if (x >= gen->map_buttons[i].x0 && x <= gen->map_buttons[i].x1
			&& y >= gen->map_buttons[i].y0 && y <= gen->map_buttons[i].y1)
		{
			start_game_from_map(gen, gen->map_buttons[i].filepath);
			return ;
		}
		i++;
	}
	if (gen->x_btn_container[0].x_btn.x0 <= x
		&& gen->x_btn_container[0].x_btn.x1 >= x
		&& gen->x_btn_container[0].x_btn.y0 <= y
		&& gen->x_btn_container[0].x_btn.y1 >= y)
	{
		back_home_menu(gen);
		return ;
	}
}

int	on_mouse_click(int button, int x, int y, t_gen *gen)
{
	if (button == MOUSE_LEFT_CLICK && !gen->in_menu && gen->ignore_next_mouse)
		add_projectile(gen);
	if (button == MOUSE_LEFT_CLICK && gen->in_menu && !gen->in_options && !gen->map_selection)
		handle_menu_click(x, y, gen);
	else if (button == MOUSE_LEFT_CLICK && gen->in_menu
		&& gen->map_selection && !gen->in_options)
		handle_map_selection_click(x, y, gen);
	else if (button == MOUSE_LEFT_CLICK && gen->in_options)
		handle_options_click(x, y, gen);
	if (gen->in_menu && gen->map_selection && !gen->in_options)
		handle_scroll(button, gen);
	if (button == MOUSE_LEFT_CLICK && gen->in_options)
	{
		if (x >= gen->dragging_slider_button.x1
			&& x <= gen->dragging_slider_button.x2
			&& y >= gen->dragging_slider_button.y1
			&& y <= gen->dragging_slider_button.y2)
			gen->dragging_slider = 1;
		if (!update_buttons(gen, x, y))
			return (0);
	}
	return (0);
}
