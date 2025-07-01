/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:02 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/01 15:45:30 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_step(t_ray *ray, t_gen *gen)
{
	if (gen->player.ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (gen->player.x - ray->map_x) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1.0 - gen->player.x) * ray->delta_distx;
	}
	if (gen->player.ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (gen->player.y - ray->map_y) * ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1.0 - gen->player.y) * ray->delta_disty;
	}
}

void	init_ray(t_ray *ray, t_gen *gen)
{
	ray->camera_x = 2 * ray->x / (double)SCREEN_X - 1;
	gen->player.ray_dir_x = gen->player.dir_x
		+ gen->player.plane_x * ray->camera_x;
	gen->player.ray_dir_y = gen->player.dir_y
		+ gen->player.plane_y * ray->camera_x;
	ray->map_x = (int)gen->player.x;
	ray->map_y = (int)gen->player.y;
	ray->delta_distx = fabs(1 / gen->player.ray_dir_x);
	ray->delta_disty = fabs(1 / gen->player.ray_dir_y);
}

void	util_check_hit(t_ray *ray, t_gen *gen)
{
	double		dist_player;
	double		dist_zombie;
	t_zombie	*z;

	z = gen->zombies;
	if (gen->map.map_matrix[ray->map_y][ray->map_x] == 'D')
	{
		dist_player = sqrt(pow(gen->player.x - (ray->map_x + 0.5), 2)
				+ pow(gen->player.y - (ray->map_y + 0.5), 2));
		while (z)
		{
			dist_zombie = sqrt(pow(z->x - (ray->map_x + 0.5), 2)
					+ pow(z->y - (ray->map_y + 0.5), 2));
			if (dist_player < 1.0 || dist_zombie < 1.0)
				return ;
			ray->hit = 1;
			ray->hit_tile = 'D';
			z = z->next;
		}
		if (dist_player >= 1.0)
		{
			ray->hit = 1;
			ray->hit_tile = 'D';
		}
	}
}

void	check_hit(t_ray *ray, t_gen *gen)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (gen->map.map_matrix[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		if (gen->map.map_matrix[ray->map_y][ray->map_x] == 'D')
			util_check_hit(ray, gen);
	}
}

void	calculate_distance(t_ray *ray, t_gen *gen)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - gen->player.x
				+ (1 - ray->step_x) / 2.0) / gen->player.ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - gen->player.y
				+ (1 - ray->step_y) / 2.0) / gen->player.ray_dir_y;
	ray->line_height = (int)(SCREEN_Y / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_Y / 2;
	ray->draw_end = ray->line_height / 2 + SCREEN_Y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= SCREEN_Y)
		ray->draw_end = SCREEN_Y - 1;
}
