/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:33:44 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/19 14:40:40 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	free_matrix(char **matrix, int height)
{
	int	i;

	i = 0;
	if (matrix[0][0] == '\n')
	{
		free(matrix[0]);
		free(matrix);
		return ;
	}
	if (height == 1)
	{
		free(matrix[0]);
		free(matrix);
		return ;
	}
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_map(t_map	*map)
{
	free_matrix(map->map_matrix, map->height);
	free(map);
} */

int	close_window(t_gen *gen)
{
	mlx_destroy_window(gen->mlx_ptr, gen->win_ptr);
	mlx_destroy_display(gen->mlx_ptr);
	free(gen->mlx_ptr);
	free(gen->map.N_tex);
	free(gen->map.S_tex);
	free(gen->map.W_tex);
	free(gen->map.E_tex);
	free(gen->map.F_tex);
	free(gen->map.C_tex);
	exit(0);
	return (0);
}
