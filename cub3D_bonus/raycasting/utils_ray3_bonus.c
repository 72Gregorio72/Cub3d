/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray3_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:59:40 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/24 17:30:23 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_X || y < 0 || y >= SCREEN_Y)
		return ;
	dst = img->data + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_image(t_gen *gen)
{
	gen->img.img_ptr = mlx_new_image(gen->mlx_ptr, SCREEN_X, SCREEN_Y);
	gen->img.data = mlx_get_data_addr(gen->img.img_ptr,
			&gen->img.bpp, &gen->img.line_length, &gen->img.endian);
	clear_image(&gen->img);
}

void	rotate_player(t_gen *gen, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = gen->player.dir_x;
	old_plane_x = gen->player.plane_x;
	gen->player.dir_x = gen->player.dir_x * cos(angle)
		- gen->player.dir_y * sin(angle);
	gen->player.dir_y = old_dir_x * sin(angle) + gen->player.dir_y * cos(angle);
	gen->player.plane_x = gen->player.plane_x * cos(angle)
		- gen->player.plane_y * sin(angle);
	gen->player.plane_y = old_plane_x * sin(angle)
		+ gen->player.plane_y * cos(angle);
}

int	is_walkable(t_gen *gen, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	return (mx >= 0 && mx < gen->map.width
		&& my >= 0 && my < gen->map.height
		&& gen->map.map_matrix[my][mx] != '1');
}

void	check_movements_util(t_gen *gen)
{
	double	new_x;
	double	new_y;

	if (gen->keys.a)
	{
		new_x = gen->player.x - gen->player.plane_x * MOVE_SPEED;
		new_y = gen->player.y - gen->player.plane_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
	if (gen->keys.d)
	{
		new_x = gen->player.x + gen->player.plane_x * MOVE_SPEED;
		new_y = gen->player.y + gen->player.plane_y * MOVE_SPEED;
		if (is_walkable(gen, new_x, gen->player.y))
			gen->player.x = new_x;
		if (is_walkable(gen, gen->player.x, new_y))
			gen->player.y = new_y;
	}
}
