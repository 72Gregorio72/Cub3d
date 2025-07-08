/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_preview_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:47:40 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/07 15:48:31 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	start_game_from_map(t_gen *gen, const char *filepath)
{
	if (!get_map((char *)filepath, gen))
	{
		ft_printf("Failed to load map: %s\n", filepath);
		free((char *)filepath);
		return ;
	}
	free(gen->map_file_path);
	gen->map_file_path = ft_strdup(filepath);
	draw_menu(gen);
}

void	draw_texture(t_img *img, t_tex *tex, int x0, int y0)
{
	int				y;
	int				x;
	char			*pixel;
	unsigned int	color;

	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			pixel = tex->data + (y * tex->line_length + x * (tex->bpp / 8));
			color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	draw_wall_cube(t_gen *gen, t_map_preview *preview)
{
	while (preview->y < preview->cube_size)
	{
		preview->x = 0;
		while (preview->x < preview->cube_size)
		{
			preview->color = 0x000000;
			if (preview->y == 0 || preview->y == preview->cube_size - 1
				|| preview->x == 0 || preview->x == preview->cube_size - 1)
				preview->color = 0xAAAAAA;
			put_pixel(&gen->img, preview->iso_x
				+ preview->x, preview->iso_y + preview->y, preview->color);
			preview->x++;
		}
		preview->y++;
	}
}

void	draw_wall_preview(t_gen *gen, t_map_preview *preview)
{
	if (gen->map.map_matrix[preview->i][preview->j] == '1')
	{
		preview->iso_x = preview->base_x
			+ (preview->j - preview->i) * preview->cube_size;
		preview->iso_y = preview->base_y
			+ (preview->j + preview->i) * preview->cube_size / 2;
		preview->y = 0;
		draw_wall_cube(gen, preview);
		preview->y = 0;
		while (preview->y < 5)
		{
			preview->x = 0;
			while (preview->x < preview->cube_size)
			{
				put_pixel(&gen->img, preview->iso_x
					+ preview->x, preview->iso_y - preview->y, 0xEEEEEE);
				preview->x++;
			}
			preview->y++;
		}
	}
}

void	draw_map_preview(t_gen *gen, int preview_origin_x, int preview_origin_y)
{
	t_map_preview	preview;

	set_preview(&preview, gen, preview_origin_x, preview_origin_y);
	preview.i = 0;
	while (preview.i < preview.map_h)
	{
		preview.j = 0;
		while (preview.j < preview.map_w)
		{
			draw_wall_preview(gen, &preview);
			preview.j++;
		}
		preview.i++;
	}
}
