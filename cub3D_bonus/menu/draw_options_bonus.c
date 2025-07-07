/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_options_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:58:28 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/07 15:58:55 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_slider(t_gen *gen, int slider_x)
{
	gen->dragging_slider_button.x1 = slider_x - 5;
	gen->dragging_slider_button.y1 = 215;
	gen->dragging_slider_button.x2 = slider_x + 5;
	gen->dragging_slider_button.y2 = 225;
	gen->player_options.mouse_sensitivity = (slider_x - 100) / 200.0;
}

void	draw_slider(t_gen *gen)
{
	int	slider_x;
	int	x;
	int	dx;
	int	dy;

	slider_x = 100 + (int)(gen->player_options.mouse_sensitivity * 200.0);
	x = 100;
	while (x <= 300)
	{
		put_pixel(&gen->img, x, 220, 0xAAAAAA);
		x++;
	}
	dx = -5;
	while (dx <= 5)
	{
		dy = -5;
		while (dy <= 5)
		{
			put_pixel(&gen->img, slider_x + dx, 220 + dy, 0xFF0000);
			dy++;
		}
		dx++;
	}
	set_slider(gen, slider_x);
}

void	set_options(t_gen *gen, t_option_data *data)
{
	data->y = 300 + data->i * 50;
	data->bx1 = 300;
	data->by1 = data->y - 10;
	data->bx2 = 360;
	data->by2 = data->y + 20;
	data->key_name = mlx_get_key_name(*(data->bindings[data->i]));
	data->tmp = ft_strjoin(data->keys[data->i], ": ");
	data->buf = ft_strjoin(data->tmp, data->key_name);
	free(data->tmp);
	free(data->keys[data->i]);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, 100,
		data->y, 0xFFFFFF, data->buf);
	free(data->buf);
	data->color = 0xAAAAAA;
	if (gen->selected_key_index == data->i)
	{
		data->color = 0xFFFFFF;
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			400, data->y + 10, 0xFFFFFF, "Press a new key");
	}
}

void	set_option_data(t_option_data *data, t_gen *gen)
{
	data->padding = 200;
	data->button_w = 100;
	data->button_h = 50;
	data->keys[0] = ft_strdup("UP");
	data->keys[1] = ft_strdup("DOWN");
	data->keys[2] = ft_strdup("LEFT");
	data->keys[3] = ft_strdup("RIGHT");
	data->bindings[0] = &gen->player_options.key_up;
	data->bindings[1] = &gen->player_options.key_down;
	data->bindings[2] = &gen->player_options.key_left;
	data->bindings[3] = &gen->player_options.key_right;
	clear_image(&gen->img);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr,
		SCREEN_X / 2 - 100, 80, 0xFFFFFF, "OPTIONS");
	mlx_string_put(gen->mlx_ptr, gen->win_ptr,
		100, 200, 0xFFFFFF, "Mouse Sensitivity:");
	draw_slider(gen);
}

void	draw_option(t_option_data *data, t_gen *gen)
{
	data->x = data->bx1;
	while (data->x <= data->bx2)
	{
		data->y2 = data->by1;
		while (data->y2 <= data->by2)
		{
			put_pixel(&gen->img, data->x, data->y2, data->color);
			data->y2++;
		}
		data->x++;
	}
	gen->key_buttons[data->i].x1 = data->bx1;
	gen->key_buttons[data->i].y1 = data->by1;
	gen->key_buttons[data->i].x2 = data->bx2;
	gen->key_buttons[data->i].y2 = data->by2;
	gen->key_buttons[data->i].key = data->bindings[data->i];
	gen->key_buttons[data->i].label = data->keys[data->i];
}
