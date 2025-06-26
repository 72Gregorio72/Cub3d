/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:28:10 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/24 17:28:10 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	free_zombies(t_zombie *zombies)
{
	t_zombie	*tmp;

	while (zombies)
	{
		tmp = zombies;
		zombies = zombies->next;
		free(tmp);
	}
}

void	free_gen(t_gen *gen, int flag)
{
	free(gen->map.n_tex);
	free(gen->map.s_tex);
	free(gen->map.w_tex);
	free(gen->map.e_tex);
	free(gen->map.f_tex);
	free(gen->map.c_tex);
	free(gen->zombie_tex);
	free(gen->map.ceil_color);
	free(gen->map.floor_color);
	if (flag)
		free_matrix(gen->map.map_matrix, gen->map.height);
	free_zombies(gen->zombies);
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
	if (gen->zombie_tex && gen->zombie_tex->img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->zombie_tex->img_ptr);
	if (gen->win_ptr)
		mlx_destroy_window(gen->mlx_ptr, gen->win_ptr);
	if (gen->mlx_ptr)
		mlx_destroy_display(gen->mlx_ptr);
	free_gen(gen, 1);
	free(gen->mlx_ptr);
	ft_lstclear_proj(&gen->projectiles);
	exit(EXIT_SUCCESS);
}

void	fill_map_row(t_gen *gen, char *line, int y)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n'
		&& line[i] != '\r' && i < gen->map.width)
	{
		if (line[i] == ' ' || line[i] == '\t')
			gen->map.map_matrix[y][i] = '2';
		else
			gen->map.map_matrix[y][i] = line[i];
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			gen->player_orientation = line[i];
			gen->arrow_orientation = gen->player_orientation;
		}
		i++;
	}
	while (i < gen->map.width)
		gen->map.map_matrix[y][i++] = '2';
}
