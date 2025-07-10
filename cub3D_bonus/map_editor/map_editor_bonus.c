/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:58:33 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 16:09:43 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define SQUARE_SIZE SCREEN_X
#define GRID_SIZE 100
#define CELL_SIZE (SQUARE_SIZE / GRID_SIZE)
#define OFFSET_X 0
#define OFFSET_Y 0
#define BACKGROUND_CELL 0x888888
#define GRID_COLOR_CELL 0xAAAAAA

void	draw_filled_square(t_gen *gen, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(gen->mlx_ptr, gen->win_ptr, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_hline(t_gen *gen, int x, int y, int length, int color)
{
	int	i;

	i = 0;
	while (i < length)
	{
		mlx_pixel_put(gen->mlx_ptr, gen->win_ptr, x + i, y, color);
		i++;
	}
}

void	draw_vline(t_gen *gen, int x, int y, int length, int color)
{
	int	i;

	i = 0;
	while (i < length)
	{
		mlx_pixel_put(gen->mlx_ptr, gen->win_ptr, x, y + i, color);
		i++;
	}
}

void	map_editor(t_gen *gen)
{
	int	i;

	gen->in_map_editor = 1;
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	draw_filled_square(gen, OFFSET_X, OFFSET_Y, SQUARE_SIZE, BACKGROUND_CELL);
	i = 0;
	while (i <= GRID_SIZE)
	{
		draw_hline(gen, OFFSET_X, OFFSET_Y + i * CELL_SIZE, SQUARE_SIZE, GRID_COLOR_CELL);
		draw_vline(gen, OFFSET_X + i * CELL_SIZE, OFFSET_Y, SQUARE_SIZE, GRID_COLOR_CELL);
		i++;
	}
}

void	update_edited_map(int edited_map[100][100], int x, int y)
{
	if (edited_map[y][x] == 0)
		edited_map[y][x] = 1;
	else
		edited_map[y][x] = 0;
}

void	draw_in_editor(int x, int y, t_gen *gen)
{
	int selected_cell_x;
	int selected_cell_y;

	selected_cell_x = x / CELL_SIZE;
	selected_cell_y = y / CELL_SIZE;
	printf("Selected cell: (%d, %d)\n", selected_cell_x, selected_cell_y);
	draw_filled_square(gen,
		OFFSET_X + selected_cell_x * CELL_SIZE,
		OFFSET_Y + selected_cell_y * CELL_SIZE,
		CELL_SIZE, 0xFFFFFF);
	update_edited_map(gen->edited_map, selected_cell_x, selected_cell_y);
}
