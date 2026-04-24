/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_listener_utils_2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:36:59 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 14:41:56 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_x_on_mouse_move(int *x)
{
	if (*x < 100)
		*x = 100;
	if (*x > 300)
		*x = 300;
}

int	on_mouse_move(int x, int y, t_gen *gen)
{
	static unsigned long	last_call;
	unsigned long			current_time;

	if (gen->dragging_slider)
	{
		set_x_on_mouse_move(&x);
		gen->player_options.mouse_sensitivity = (x - 100) / 200.0;
		if (gen->player_options.mouse_sensitivity <= 0)
			gen->player_options.mouse_sensitivity = 0.1;
		last_call = 0;
		current_time = get_current_time();
		if (current_time - last_call >= 10)
		{
			open_options_menu(gen);
			last_call = current_time;
		}
	}
	if (gen->in_menu && gen->map_selection)
		return (0);
	if (!gen->mouse_initialized)
		return (gen->mouse_initialized = 1, 0);
	if (!gen->in_menu)
		mouse_check(x, y, gen);
	return (0);
}

void	handle_map_selection_click(int x, int y, t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->map_button_count)
	{
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
	if (button == MOUSE_LEFT_CLICK && gen->in_menu
		&& !gen->in_options && !gen->map_selection)
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
