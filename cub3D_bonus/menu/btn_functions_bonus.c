/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:41:33 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/10 14:05:32 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	start_game(t_gen *gen)
{
	gen->in_menu = 0;
	reset_player(gen);
}

void	open_map_selection(t_gen *gen)
{
	gen->map_selection = 1;
	clear_image(&gen->img);
	draw_map_selector(gen);
}

void	back_home_menu(t_gen *gen)
{
	gen->in_menu = 1;
	if (gen->map_selection)
		gen->map_selection = 0;
	clear_image(&gen->img);
	draw_menu(gen);
}

void	exit_game(t_gen *gen)
{
	close_window(gen);
}

void	set_button(t_menu_button *button,
		t_draw_data data, void (*action)(t_gen *))
{
	button->x0 = data.x0;
	button->y0 = data.y0;
	button->x1 = data.x1;
	button->y1 = data.y1;
	button->action = action;
}
