/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:55:08 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/20 15:33:50 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_check(t_gen *gen)
{
	int	i;
	int	j;
	int	count_n;

	i = 0;
	count_n = 0;
	while (i < gen->map.height)
	{
		j = 0;
		while (gen->map.map_matrix[i][j])
		{
			if (gen->map.map_matrix[i][j] != 'N'
				&& gen->map.map_matrix[i][j] != '0'
				&& gen->map.map_matrix[i][j] != '1'
				&& gen->map.map_matrix[i][j] != '2'
				&& gen->map.map_matrix[i][j] != 'S'
				&& gen->map.map_matrix[i][j] != 'W'
				&& gen->map.map_matrix[i][j] != 'E')
				return (printf(RED"Error: wrong map!\n"RESET), 0);
			if (gen->map.map_matrix[i][j] == 'N'
				|| gen->map.map_matrix[i][j] == 'S'
				|| gen->map.map_matrix[i][j] == 'E'
				|| gen->map.map_matrix[i][j] == 'W')
				count_n++;
			j++;
		}
		i++;
	}
	if (count_n != 1)
		return (printf(RED"Error: wrong number of starting positions!\n"RESET), 0);
	return (1);
}
