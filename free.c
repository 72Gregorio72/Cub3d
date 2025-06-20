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

void	free_matrix(char **matrix, int height)
{
	int	i;

	if (!matrix)
		return;
	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_gen(t_gen * gen, int flag)
{
	free(gen->map.N_tex);
	free(gen->map.S_tex);
	free(gen->map.W_tex);
	free(gen->map.E_tex);
	free(gen->map.F_tex);
	free(gen->map.C_tex);
	free(gen->map.ceil_color);
	free(gen->map.floor_color);
	if (flag)
		free_matrix(gen->map.map_matrix, gen->map.height);
}

int	close_window(t_gen *gen)
{
	if (gen->img.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->img.img_ptr);

	if (gen->map.north.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.north.img_ptr);
	if (gen->map.south.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.south.img_ptr);
	if (gen->map.east.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.east.img_ptr);
	if (gen->map.west.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.west.img_ptr);

	if (gen->win_ptr)
		mlx_destroy_window(gen->mlx_ptr, gen->win_ptr);
	if (gen->mlx_ptr)
		mlx_destroy_display(gen->mlx_ptr);
	free_gen(gen, 1);
	free(gen->mlx_ptr);
	exit(EXIT_SUCCESS);
}
