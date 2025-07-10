/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:57 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 12:50:01 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_press(int keycode, t_gen *gen)
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
}

int	on_key_press(int keycode, t_gen *gen)
{
	check_press(keycode, gen);
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
	if (keycode == KB_Q)
		gen->door.flag_door_open = 1;
	return (0);
}

void	mouse_check(int x, int y, t_gen *gen)
{
	int				delta_x;
	int				delta_y;
	double			angle;

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
}

int	on_mouse_move(int x, int y, t_gen *gen)
{
	if (gen->dragging_slider)
	{
		if (x < 100)
			x = 100;
		if (x > 300)
			x = 300;
		gen->player_options.mouse_sensitivity = (x - 100) / 200.0;
		if (gen->player_options.mouse_sensitivity <= 0)
			gen->player_options.mouse_sensitivity = 0.1;
		static unsigned long last_call = 0;
		unsigned long current_time = get_current_time();
		if (current_time - last_call >= 10)
		{
			open_options_menu(gen);
			last_call = current_time;
		}
	}
	if (gen->in_menu && gen->map_selection)
		return (0);
	if (!gen->mouse_initialized)
	{
		gen->mouse_initialized = 1;
		return (0);
	}
	if (!gen->in_menu)
		mouse_check(x, y, gen);
	return (0);
}
