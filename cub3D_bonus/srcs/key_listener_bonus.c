/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:57 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/30 14:18:38 by gpicchio         ###   ########.fr       */
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
	if (keycode == KB_W)
		gen->keys.w = 1;
	if (keycode == KB_A)
		gen->keys.a = 1;
	if (keycode == KB_S)
		gen->keys.s = 1;
	if (keycode == KB_D)
		gen->keys.d = 1;
	if (keycode == KB_LEFT)
		gen->keys.left = 1;
	if (keycode == KB_RIGHT)
		gen->keys.right = 1;
	return (0);
}

int	on_key_release(int keycode, t_gen *gen)
{
	if (keycode == KB_W)
		gen->keys.w = 0;
	if (keycode == KB_A)
		gen->keys.a = 0;
	if (keycode == KB_S)
		gen->keys.s = 0;
	if (keycode == KB_D)
		gen->keys.d = 0;
	if (keycode == KB_LEFT)
		gen->keys.left = 0;
	if (keycode == KB_RIGHT)
		gen->keys.right = 0;
	return (0);
}

int	on_mouse_move(int x, int y, t_gen *gen)
{
	const double	sensitivity = 0.0005;
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
		angle = -delta_x * sensitivity;
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

int	on_mouse_click(int button, int x, int y, t_gen *gen)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_CLICK)
		add_projectile(gen);
	return (0);
}
