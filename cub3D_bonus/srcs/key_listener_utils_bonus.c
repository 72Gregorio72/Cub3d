/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:36:59 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/04 17:47:25 by vcastald         ###   ########.fr       */
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

void	handle_menu_click(int x, int y, t_gen *gen)
{
	t_map_button	btn;
	int				i;

	i = 0;
	while (i < gen->map_button_count)
	{
		btn = gen->map_buttons[i];
		if (x >= btn.x0 && x <= btn.x1 && y >= btn.y0 && y <= btn.y1)
		{
			if (btn.filepath)
				start_game_from_map(gen, btn.filepath);
			else if (btn.action)
				btn.action(gen);
			gen->ignore_next_mouse = 1;
			break ;
		}
		i++;
	}
	if (!update_buttons(gen, x, y))
		return ;
}

void	handle_slider_and_scroll(int button, int x, int y, t_gen *gen)
{
	if (button == MOUSE_LEFT_CLICK)
	{
		if (x >= gen->dragging_slider_button.x1
			&& x <= gen->dragging_slider_button.x2
			&& y >= gen->dragging_slider_button.y1
			&& y <= gen->dragging_slider_button.y2)
			gen->dragging_slider = 1;
	}
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

int	on_mouse_click(int button, int x, int y, t_gen *gen)
{
	if (button == MOUSE_LEFT_CLICK && !gen->in_menu && gen->ignore_next_mouse)
		add_projectile(gen);
	if (button == MOUSE_LEFT_CLICK && gen->in_menu)
		handle_menu_click(x, y, gen);
	if (gen->in_menu && gen->map_selection)
		handle_slider_and_scroll(button, x, y, gen);
	return (0);
}
