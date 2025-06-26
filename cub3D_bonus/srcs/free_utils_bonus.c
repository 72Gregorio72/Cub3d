/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:42:14 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/26 12:42:27 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	unclosed_zero(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (map->map_matrix[i][j])
		{
			if (map->map_matrix[i][j] == '0')
			{
				if (i == 0 || i == map->height - 1
					|| j == 0 || !map->map_matrix[i][j + 1]
					|| j >= (int)ft_strlen(map->map_matrix[i - 1])
					|| j >= (int)ft_strlen(map->map_matrix[i + 1])
					|| map->map_matrix[i + 1][j] == '2'
					|| map->map_matrix[i - 1][j] == '2'
					|| map->map_matrix[i][j + 1] == '2'
					|| map->map_matrix[i][j - 1] == '2')
					return (0);
			}
			j++;
		}
	}
	return (1);
}
