/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw_minigame_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:41:08 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/01 15:41:32 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	util_calculate_prog(t_draw_data d, t_gen *gen, int x, int y)
{
	y = -d.radius;
	while (y <= d.radius)
	{
		x = -d.radius;
		while (x <= d.radius)
		{
			if (x * x + y * y <= d.radius * d.radius)
			{
				d.px = d.screen_x + x;
				d.py = d.screen_y + y;
				if (d.px >= 0 && d.px < SCREEN_X
					&& d.py >= 0 && d.py < SCREEN_Y)
					put_pixel(&gen->img, d.px, d.py, 0xFF0000);
			}
			x++;
		}
		y++;
	}
}
