/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:37:00 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/10 14:37:53 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	if (gen->title_tex.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->title_tex.img_ptr);
	util_close_window(gen);
	free_all_buttons(gen);
	destroy_zombie_tex(gen);
	if (gen->win_ptr)
		mlx_destroy_window(gen->mlx_ptr, gen->win_ptr);
	if (gen->mlx_ptr)
	{
		mlx_destroy_display(gen->mlx_ptr);
		free(gen->mlx_ptr);
	}
	ft_lstclear_proj(&gen->projectiles);
	free_gen(gen, 1);
	exit(EXIT_SUCCESS);
}

void	free_matrix(char **matrix, int height)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
