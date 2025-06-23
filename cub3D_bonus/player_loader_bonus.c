/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loader_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:09:45 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/23 12:09:45 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_player_position(t_gen *gen)
{
	int	y;
	int	x;

	y = -1;
	while (++y < gen->map.height)
	{
		x = 0;
		while (x < gen->map.width)
		{
			if (gen->map.map_matrix[y][x] == 'N'
				|| gen->map.map_matrix[y][x] == 'E'
				|| gen->map.map_matrix[y][x] == 'W'
				|| gen->map.map_matrix[y][x] == 'S')
			{
				gen->player.x = x + 0.5;
				gen->player.y = y + 0.5;
				gen->player.dir_x = 0;
				gen->player.dir_y = -1;
				gen->player.plane_x = 0.66;
				gen->player.plane_y = 0;
				return ;
			}
			x++;
		}
	}
}
