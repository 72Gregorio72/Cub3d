/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:55:08 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/20 13:55:27 by vcastald         ###   ########.fr       */
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
				&& gen->map.map_matrix[i][j] != '2')
				return (printf(RED"Error: wrong map!\n"RESET), 0);
			if (gen->map.map_matrix[i][j] == 'N')
				count_n++;
			j++;
		}
		i++;
	}
	if (count_n != 1)
		return (printf(RED"Error: wrong map!\n"RESET), 0);
	return (1);
}
