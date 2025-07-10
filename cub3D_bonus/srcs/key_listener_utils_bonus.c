/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:36:59 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 16:00:31 by gpicchio         ###   ########.fr       */
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
	if (button == MOUSE_LEFT_CLICK && gen->in_map_editor)
	{
		gen->is_drawing = 0;
		return (0);
	}
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
	while (i < 5)
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
