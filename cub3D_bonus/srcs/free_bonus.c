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
	free(gen->map.ceil_color);
	free(gen->map.floor_color);
	free(gen->map_file_path);
	if (flag)
		free_matrix(gen->map.map_matrix, gen->map.height);
	free_zombies(gen->zombies);
}

void	destroy_zombie_tex(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < 26)
	{
		if (gen->zombie_tex_walking[i])
		{
			if (gen->zombie_tex_walking[i]->img_ptr)
				mlx_destroy_image(gen->mlx_ptr,
					gen->zombie_tex_walking[i]->img_ptr);
			free(gen->zombie_tex_walking[i]);
		}
	}
	i = -1;
	while (++i < 17)
	{
		if (gen->zombie_tex_attacking[i])
		{
			if (gen->zombie_tex_attacking[i]->img_ptr)
				mlx_destroy_image(gen->mlx_ptr,
					gen->zombie_tex_attacking[i]->img_ptr);
			free(gen->zombie_tex_attacking[i]);
		}
	}
	util_destroy_zombie_tex(gen);
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
