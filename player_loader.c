/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:39:19 by marvin            #+#    #+#             */
/*   Updated: 2025/06/20 09:39:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_position(t_gen *gen)
{
	int	y = 0;
	int	x;

	while (y < gen->map.height)
	{
		x = 0;
		while (x < gen->map.width)
		{
			if (gen->map.map_matrix[y][x] == 'N')
			{
				gen->player.x = x + 0.5;
				gen->player.y = y + 0.5;
				gen->player.dir_x = 0;
				gen->player.dir_y = -1;
				gen->player.plane_x = 0.66;
				gen->player.plane_y = 0;
				gen->map.map_matrix[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
