/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:59:00 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/10 10:43:02 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_zombies(t_gen *gen)
{
	int	i;
	int	j;

	gen->zombies = NULL;
	gen->num_zombies = 0;
	i = 0;
	while (i < gen->map.height)
	{
		j = 0;
		while (j < gen->map.width)
		{
			if (gen->map.map_matrix[i][j] == 'Z')
				add_zombie(gen, j + 0.5, i + 0.5);
			j++;
		}
		i++;
	}
}

void	load_img(t_gen *gen)
{
	load_textures(gen);
	load_zombies(gen);
	load_button_images(gen);
	rotate_view(gen);
	set_map_buttons(gen);
}

void	util_rotate_player(t_gen *gen)
{
	if (gen->keys.left)
		rotate_player(gen, -ROTATE_SPEED);
	if (gen->keys.right)
		rotate_player(gen, ROTATE_SPEED);
}

void	util_destroy_zombie_tex(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < 21)
	{
		if (gen->zombie_tex_dead[i])
		{
			if (gen->zombie_tex_dead[i]->img_ptr)
				mlx_destroy_image(gen->mlx_ptr,
					gen->zombie_tex_dead[i]->img_ptr);
			free(gen->zombie_tex_dead[i]);
		}
	}
	i = 0;
	while (i < 13)
	{
		if (gen->zombie_tex_hit[i])
		{
			if (gen->zombie_tex_hit[i]->img_ptr)
				mlx_destroy_image(gen->mlx_ptr,
					gen->zombie_tex_hit[i]->img_ptr);
			free(gen->zombie_tex_hit[i]);
		}
		i++;
	}
}
