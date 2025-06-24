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

void	draw_minimap(t_map *map, t_gen *gen)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map_matrix[i][j])
		{
			if (map->map_matrix[i][j] == '1')
				put_pixel(&gen->img, i, j, 0x000000);
			else if (map->map_matrix[i][j] == '0')
				put_pixel(&gen->img, i, j, 0xFFFFFF);
		}
	}
}
