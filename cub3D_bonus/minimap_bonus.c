/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:10:48 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/24 17:20:18 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define TILE_SIZE 10

void	draw_minimap(t_map *map, t_gen *gen)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map_matrix[i][j])
		{
			if (map->map_matrix[i][j] == '1')
				color = 0xFF0000;
			else if (map->map_matrix[i][j] == '0')
				color = 0xFFFF00;
			else if (map->map_matrix[i][j] == gen->player_orientation)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			y = 0;
			while (y < TILE_SIZE)
			{
				x = 0;
				while (x < TILE_SIZE)
				{
					put_pixel(&gen->img,
						j * TILE_SIZE + x, i * TILE_SIZE + y, color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}


