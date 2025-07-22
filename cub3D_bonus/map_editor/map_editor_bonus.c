/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:58:33 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/22 15:21:51 by marvin           ###   ########.fr       */
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


void	read_map_template(int fd, char ***edited_map)
{
	char	*line;
	int		i;

	i = 0;
	*edited_map = malloc(sizeof(char *) * 100);
	if (!(*edited_map))
		return ;
	line = get_next_line(fd);
	while (line && i < 100)
	{
		(*edited_map)[i] = ft_strdup(line);
		free(line);
		if (!(*edited_map)[i])
			break ;
		i++;
		line = get_next_line(fd);
	}
	(*edited_map)[i] = NULL;
	close(fd);
}

char	**get_map_template(t_gen *gen)
{
	int		fd;
	char	**template_map;

	fd = open("map_template.cub", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening map template");
		draw_menu(gen);
		return (NULL);
	}
	read_map_template(fd, &template_map);
	close(fd);
	if (!template_map)
	{
		printf("Error reading map template");
		draw_menu(gen);
		return (NULL);
	}
	return (template_map);
}

void	create_map_file(t_gen *gen)
{
	int		fd;
	char	*map_name = NULL;
	char	*map_path = NULL;
	char	*index_str = NULL;
	int		index = 0;
	int		map_written = 0;

	char **template_map = get_map_template(gen);
	if (!template_map)
		return ;
	while (1)
	{
		index_str = ft_itoa(index);
		if (!index_str)
			return ;
		map_path = ft_strjoin("maps/map", index_str);
		free(index_str);
		if (!map_path)
			return ;
		map_name = ft_strjoin(map_path, ".cub");
		free(map_path);
		if (!map_name)
			return ;
		fd = open(map_name, O_RDONLY);
		if (fd < 0)
			break ;
		close(fd);
		free(map_name);
		map_name = NULL;
		index++;
	}
	fd = open(map_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(map_name);
		return ;
	}
	for (int i = 0; template_map[i]; i++)
	{
		if (ft_strncmp(template_map[i], "map here:", 9) == 0 && !map_written)
		{
			for (int j = 0; j < 100; j++)
			{
				for (int k = 0; k < 100; k++)
				{
					printf("Writing map at (%d, %d): %d\n", j, k, gen->edited_map[j][k]);
					ft_putstr_fd(ft_itoa(gen->edited_map[j][k]), fd);
				}
				write(fd, "\n", 1);
			}
			map_written = 1;
		}
		else
		{
			ft_putstr_fd(template_map[i], fd);
			write(fd, "\n", 1);
		}
	}
	close(fd);
	free(map_name);
	for (int i = 0; template_map[i]; i++)
		free(template_map[i]);
	free(template_map);
}

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

void	draw_buttons(t_gen *gen)
{
	int	button_x;
	int	button_y;
	int	button_size;

	button_x = SCREEN_X / 2;
	button_y = SCREEN_Y / 2;
	button_size = 50;

	draw_filled_square(gen, button_x, button_y, button_size, 0xFF0000);
	gen->map_editor.done_btn.x0 = button_x;
	gen->map_editor.done_btn.y0 = button_y;
	gen->map_editor.done_btn.x1 = button_x + button_size;
	gen->map_editor.done_btn.y1 = button_y + button_size;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, button_x + 10, button_y + 15, 0xFFFFFF, "Exit");
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
	draw_buttons(gen);
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
	draw_filled_square(gen,
		OFFSET_X + selected_cell_x * CELL_SIZE,
		OFFSET_Y + selected_cell_y * CELL_SIZE,
		CELL_SIZE, 0xFFFFFF);
	update_edited_map(gen->edited_map, selected_cell_x, selected_cell_y);
}
