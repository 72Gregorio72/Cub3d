/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_healthbar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:29:53 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/26 15:29:54 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_healthbar(t_gen *gen)
{
	int	health_bar_width = 200;
	int	health_bar_height = 30;
	int	x = SCREEN_X - health_bar_width - 20;
	int	y = 20;
	int	health_percentage = (gen->health * 100) / gen->max_health;
	int	health_color = 0x00FF00;
	
	for (int i = 0; i < health_bar_height; i++)
	{
		for (int j = 0; j < health_bar_width; j++)
			put_pixel(&gen->img, x + j, y + i, 0x000000);
	}
	for (int i = 0; i < health_bar_height; i++)
	{
		for (int j = 0; j < (health_bar_width * health_percentage / 100); j++)
			put_pixel(&gen->img, x + j, y + i, health_color);
	}
}
