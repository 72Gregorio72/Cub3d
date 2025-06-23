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

static void	draw_texture_column(t_ray *ray, t_gen *gen, t_tex *tex, int tex_x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	char	*pixel;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_Y / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		pixel = tex->data + (tex_y * tex->line_length + tex_x * (tex->bpp / 8));
		put_pixel(&gen->img, ray->x, y, *(unsigned int *)pixel);
		y++;
	}
	ray->x++;
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	draw_ceiling_and_floor(t_ray *ray, t_gen *gen)
{
	int				i;
	unsigned int	color;

	i = 0;
	color = rgb_to_hex(gen->map.floor_color[0],
			gen->map.floor_color[1], gen->map.floor_color[2]);
	while (i < ray->draw_start)
	{
		put_pixel(&gen->img, ray->x, i, color);
		i++;
	}
	i = ray->draw_end;
	color = rgb_to_hex(gen->map.ceil_color[0],
			gen->map.ceil_color[1], gen->map.ceil_color[2]);
	while (i < SCREEN_Y)
	{
		put_pixel(&gen->img, ray->x, i, color);
		i++;
	}
}

void	draw_map(t_ray *ray, t_gen *gen)
{
	t_tex	*tex;
	double	wall_x;
	int		tex_x;

	tex = select_texture(ray, gen);
	if (ray->side == 0)
		wall_x = gen->player.y + ray->perp_wall_dist * gen->player.ray_dir_y;
	else
		wall_x = gen->player.x + ray->perp_wall_dist * gen->player.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && gen->player.ray_dir_x > 0)
		|| (ray->side == 1 && gen->player.ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	draw_texture_column(ray, gen, tex, tex_x);
	draw_ceiling_and_floor(ray, gen);
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
