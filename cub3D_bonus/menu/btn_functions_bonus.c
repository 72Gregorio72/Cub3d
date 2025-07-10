/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:41:33 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/10 11:14:06 by gpicchio         ###   ########.fr       */
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
	int x0, int y0, int x1, int y1, void (*action)(t_gen *))
{
	button->x0 = x0;
	button->y0 = y0;
	button->x1 = x1;
	button->y1 = y1;
	button->action = action;
}
