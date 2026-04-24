/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_healthbar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:29:53 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/01 15:52:28 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_healthbar(t_gen *gen)
{
	int	health_bar_width;
	int	health_bar_height;
	int	health_percentage;
	int	i;
	int	j;

	health_bar_width = 200;
	health_bar_height = 30;
	health_percentage = (gen->health * 100) / gen->max_health;
	i = -1;
	while (++i < health_bar_height)
	{
		j = -1;
		while (++j < health_bar_width)
			put_pixel(&gen->img,
				SCREEN_X - health_bar_width - 20 + j, 20 + i, 0x000000);
	}
	i = -1;
	while (++i < health_bar_height)
	{
		j = -1;
		while (++j < (health_bar_width * health_percentage / 100))
			put_pixel(&gen->img,
				SCREEN_X - health_bar_width - 20 + j, 20 + i, 0x00FF00);
	}
}
