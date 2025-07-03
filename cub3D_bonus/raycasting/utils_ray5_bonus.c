/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray5_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:30 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 09:59:17 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	zombie_in_door(t_gen *gen)
{
	t_zombie	*z;

	z = gen->zombies;
	while (z)
	{
		if (gen->map.map_matrix[(int)z->y][(int)z->x] == 'D')
			return (1);
		z = z->next;
	}
	return (0);
}

t_tex	*select_texture_door(t_gen *gen)
{
	if (gen->door.dist_player >= 3.0 || gen->door.dist_zombie >= 3.0)
		return (&gen->door.door_closed);
	else if ((gen->door.dist_player >= 1.0 && gen->door.dist_player < 2.0)
		|| (gen->door.dist_zombie >= 1.0 && gen->door.dist_zombie < 2.0))
		return (&gen->door.door_open);
	else if ((gen->door.dist_player >= 2.0 && gen->door.dist_player < 3.0)
		|| (gen->door.dist_zombie >= 2.0 && gen->door.dist_zombie < 3.0))
		return (&gen->door.door_half_open);
	return (NULL);
}

void	draw_doors(t_gen *gen, t_ray *ray)
{
	int		tex_x;
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	t_tex	*tmp;

	tmp = select_texture_door(gen);
	if (!tmp)
		return ;
	if (tmp)
	{
		ray_dir_x = gen->player.dir_x + gen->player.plane_x * ray->camera_x;
		ray_dir_y = gen->player.dir_y + gen->player.plane_y * ray->camera_x;
		wall_x = gen->player.x + ray->perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * tmp->width);
		if (ray_dir_y < 0)
			tex_x = tmp->width - tex_x - 1;
		draw_texture_column(ray, gen, tmp, tex_x);
		draw_ceiling_and_floor(ray, gen);
	}
}
