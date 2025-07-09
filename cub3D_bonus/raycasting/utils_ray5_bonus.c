/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray5_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:30 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 12:57:43 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	zombie_near_door(t_gen *gen, t_ray *ray)
{
	t_zombie	*z;
	double		door_x;
	double		door_y;
	double		dist;

	z = gen->zombies;
	door_x = ray->map_x + 0.5;
	door_y = ray->map_y + 0.5;
	while (z)
	{
		dist = sqrt(pow(z->x - door_x, 2) + pow(z->y - door_y, 2));
		if (dist < 1.0)
			return (1);
		z = z->next;
	}
	return (0);
}

void	draw_doors(t_gen *gen, t_ray *ray)
{
	int		tex_x;
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = gen->player.dir_x + gen->player.plane_x * ray->camera_x;
	ray_dir_y = gen->player.dir_y + gen->player.plane_y * ray->camera_x;
	wall_x = gen->player.x + ray->perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * gen->door.door_closed.width);
	if (ray_dir_y < 0)
		tex_x = gen->door.door_closed.width - tex_x - 1;
	draw_texture_column(ray, gen, &gen->door.door_closed, tex_x);
	draw_ceiling_and_floor(ray, gen);
}
