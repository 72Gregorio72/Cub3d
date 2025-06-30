/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray5_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:12:30 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/30 15:12:59 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	tex_x = (int)(wall_x * gen->door_tex.width);
	if (ray_dir_y < 0)
		tex_x = gen->door_tex.width - tex_x - 1;
	draw_texture_column(ray, gen, &gen->door_tex, tex_x);
	draw_ceiling_and_floor(ray, gen);
}
