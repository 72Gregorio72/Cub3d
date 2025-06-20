/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:43:11 by marvin            #+#    #+#             */
/*   Updated: 2025/06/20 09:43:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_step(t_ray *ray, t_gen *gen)
{
	if (gen->player.ray_dir_x < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (gen->player.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - gen->player.x) * ray->deltaDistX;
	}

	if (gen->player.ray_dir_y < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (gen->player.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - gen->player.y) * ray->deltaDistY;
	}
}

void	init_ray(t_ray *ray, t_gen *gen)
{
	ray->cameraX = 2 * ray->x / (double)SCREEN_X - 1;
	gen->player.ray_dir_x = gen->player.dir_x + gen->player.plane_x * ray->cameraX;
	gen->player.ray_dir_y = gen->player.dir_y + gen->player.plane_y * ray->cameraX;
	ray->mapX = (int)gen->player.x;
	ray->mapY = (int)gen->player.y;
	ray->deltaDistX = fabs(1 / gen->player.ray_dir_x);
	ray->deltaDistY = fabs(1 / gen->player.ray_dir_y);
}

void	check_hit(t_ray *ray, t_gen *gen)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (gen->map.map_matrix[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void	calculate_distance(t_ray *ray, t_gen *gen)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - gen->player.x + (1 - ray->stepX) / 2.0) / gen->player.ray_dir_x;
	else
		ray->perpWallDist = (ray->mapY - gen->player.y + (1 - ray->stepY) / 2.0) / gen->player.ray_dir_y;
	ray->lineHeight = (int)(SCREEN_Y / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + SCREEN_Y / 2;
	ray->drawEnd = ray->lineHeight / 2 + SCREEN_Y / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= SCREEN_Y)
		ray->drawEnd = SCREEN_Y - 1;
}

void	draw_map_col(t_ray *ray, t_gen *gen)
{
	int		y;

	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		put_pixel(&gen->img, ray->x, y, (ray->side == 0) ? 0xFF0000 : 0x00FF00);
		y++;
	}
	ray->x++;
}

void	clear_image(t_img *img)
{
	int	y;

	y = 0;
	while (y < SCREEN_Y)
	{
		ft_bzero(img->data + y * img->line_length, img->line_length);
		y++;
	}
}


static t_tex	*select_texture(t_ray *ray, t_gen *gen)
{
	if (ray->side == 0)
		return (gen->player.ray_dir_x < 0) ? &gen->map.west : &gen->map.east;
	else
		return (gen->player.ray_dir_y < 0) ? &gen->map.north : &gen->map.south;
}

static void	draw_texture_column(t_ray *ray, t_gen *gen, t_tex *tex, int tex_x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	step = 1.0 * tex->height / ray->lineHeight;
	tex_pos = (ray->drawStart - SCREEN_Y / 2 + ray->lineHeight / 2) * step;
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		char *pixel = tex->data + (tex_y * tex->line_length + tex_x * (tex->bpp / 8));
		color = *(unsigned int *)pixel;
		put_pixel(&gen->img, ray->x, y, color);
		y++;
	}
	ray->x++;
}

void	draw_map(t_ray *ray, t_gen *gen)
{
	t_tex	*tex;
	double	wall_x;
	int		tex_x;

	tex = select_texture(ray, gen);
	if (ray->side == 0)
		wall_x = gen->player.y + ray->perpWallDist * gen->player.ray_dir_y;
	else
		wall_x = gen->player.x + ray->perpWallDist * gen->player.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && gen->player.ray_dir_x > 0) || (ray->side == 1 && gen->player.ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	draw_texture_column(ray, gen, tex, tex_x);
}

void	raycasting(t_gen *gen)
{
	t_ray	ray;

	ray.x = 0;
	while (ray.x < SCREEN_X)
	{
		init_ray(&ray, gen);
		get_step(&ray, gen);
		check_hit(&ray, gen);
		calculate_distance(&ray, gen);
		draw_map(&ray, gen);
	}
}
