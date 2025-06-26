/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:42:14 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/26 13:40:17 by vcastald         ###   ########.fr       */
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

void	ft_lstclear_proj(t_projectile **stackA)
{
	t_projectile	*temp;

	temp = NULL;
	while (*stackA)
	{
		temp = (*stackA)->next;
		free(*stackA);
		*stackA = NULL;
		if (temp == NULL)
			break ;
		*stackA = temp;
	}
}
