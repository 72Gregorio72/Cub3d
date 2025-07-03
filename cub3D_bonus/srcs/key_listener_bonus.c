/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:57 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/03 14:29:27 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	on_key_press(int keycode, t_gen *gen)
{
	if (keycode == KB_ESC)
	{
		close_window(gen);
		exit(0);
	}
	if (keycode == gen->player_options.key_up)
		gen->keys.w = 1;
	if (keycode == gen->player_options.key_down)
		gen->keys.s = 1;
	if (keycode == gen->player_options.key_left)
		gen->keys.a = 1;
	if (keycode == gen->player_options.key_right)
		gen->keys.d = 1;
	if (keycode == KB_LEFT)
		gen->keys.left = 1;
	if (keycode == KB_RIGHT)
		gen->keys.right = 1;
	if (gen->waiting_key_for)
	{
		if (gen->waiting_key_for == 1)
			gen->player_options.key_up = keycode;
		else if (gen->waiting_key_for == 2)
			gen->player_options.key_down = keycode;
		else if (gen->waiting_key_for == 3)
			gen->player_options.key_left = keycode;
		else if (gen->waiting_key_for == 4)
			gen->player_options.key_right = keycode;
		gen->waiting_key_for = 0;
		open_options_menu(gen);
		return (0);
	}
	return (0);
}

int	on_key_release(int keycode, t_gen *gen)
{
	if (keycode == gen->player_options.key_up)
		gen->keys.w = 0;
	if (keycode == gen->player_options.key_down)
		gen->keys.s = 0;
	if (keycode == gen->player_options.key_left)
		gen->keys.a = 0;
	if (keycode == gen->player_options.key_right)
		gen->keys.d = 0;
	if (keycode == KB_LEFT)
		gen->keys.left = 0;
	if (keycode == KB_RIGHT)
		gen->keys.right = 0;
	if (keycode == KB_E)
		draw_menu(gen);
	return (0);
}

int	on_mouse_move(int x, int y, t_gen *gen)
{
	if (gen->dragging_slider)
	{
		if (x < 100) x = 100;
		if (x > 300) x = 300;
		gen->player_options.mouse_sensitivity = (x - 100) / 200.0;
		if (gen->player_options.mouse_sensitivity <= 0)
			gen->player_options.mouse_sensitivity = 0.1;
		open_options_menu(gen);
	}
	if (gen->in_menu)
		return (0);
	int				delta_x;
	int				delta_y;
	double			angle;

	if (!gen->mouse_initialized)
	{
		gen->mouse_initialized = 1;
		return (0);
	}
	delta_x = x - (SCREEN_X / 2);
	delta_y = y - (SCREEN_Y / 2);
	if (abs(delta_x) > 1)
	{
		angle = -delta_x * (gen->player_options.mouse_sensitivity * 0.001);
		rotate_player(gen, -angle);
	}
	if (abs(delta_y) > 1)
	{
		gen->mouse_vertical_offset += delta_y;
		if (gen->mouse_vertical_offset < -500)
			gen->mouse_vertical_offset = -500;
		else if (gen->mouse_vertical_offset > 500)
			gen->mouse_vertical_offset = 500;
	}
	mlx_mouse_move(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2, SCREEN_Y / 2);
	return (0);
}

char	*mlx_get_key_name(int keycode)
{
	if (keycode >= 'A' && keycode <= 'Z')
	{
		static char s[2] = {0};
		s[0] = keycode;
		return (s);
	}
	if (keycode >= 'a' && keycode <= 'z')
	{
		static char s[2] = {0};
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

int	on_mouse_click(int button, int x, int y, t_gen *gen)
{
	if (button == MOUSE_LEFT_CLICK && !gen->in_menu && gen->ignore_next_mouse)
		add_projectile(gen);
	if (button == MOUSE_LEFT_CLICK && gen->in_menu)
	{
		for (int i = 0; i < gen->map_button_count; i++)
		{
			t_map_button btn = gen->map_buttons[i];
			if (x >= btn.x0 && x <= btn.x1 && y >= btn.y0 && y <= btn.y1)
			{
				if (btn.filepath)
					start_game_from_map(gen, btn.filepath);
				else if (btn.action)
					btn.action(gen);
				gen->ignore_next_mouse = 1;
				break ;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			t_key_button btn = gen->key_buttons[i];
			if (x >= btn.x1 && x <= btn.x2 && y >= btn.y1 && y <= btn.y2)
			{
				gen->selected_key_index = i;
				gen->waiting_key_for = i + 1;
				return (0);
			}
		}
	}
	if (button == MOUSE_LEFT_CLICK)
	{
		if (x >= gen->dragging_slider_button.x1 && x <= gen->dragging_slider_button.x2
				&& y >= gen->dragging_slider_button.y1 && y <= gen->dragging_slider_button.y2)
			gen->dragging_slider = 1;
	}
	if (gen->in_menu)
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
	return (0);
}
