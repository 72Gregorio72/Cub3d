/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:58:33 by gpicchio          #+#    #+#             */
/*   Updated: 2025/08/05 14:09:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define SQUARE_SIZE SCREEN_X
#define GRID_SIZE EDITED_MAP_GRID_SIZE
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
	*edited_map = malloc(sizeof(char *) * EDITED_MAP_GRID_SIZE);
	if (!(*edited_map))
		return ;
	line = get_next_line(fd);
	while (line && i < EDITED_MAP_GRID_SIZE)
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

void flood_fill_from_edge(int **map, int size, int x, int y, int mark)
{
	if (x < 0 || x >= size || y < 0 || y >= size)
		return;
	if (map[y][x] != 2)
		return;
	map[y][x] = mark;
	flood_fill_from_edge(map, size, x+1, y, mark);
	flood_fill_from_edge(map, size, x-1, y, mark);
	flood_fill_from_edge(map, size, x, y+1, mark);
	flood_fill_from_edge(map, size, x, y-1, mark);
}

void	fill_playable_spaces(t_gen *gen)
{
	int **tmp_map = malloc(EDITED_MAP_GRID_SIZE * sizeof(int*));
	for (int i = 0; i < EDITED_MAP_GRID_SIZE; i++)
	{
		tmp_map[i] = malloc(EDITED_MAP_GRID_SIZE * sizeof(int));
		for (int j = 0; j < EDITED_MAP_GRID_SIZE; j++)
			tmp_map[i][j] = gen->edited_map[i][j];
	}
	for (int i = 0; i < EDITED_MAP_GRID_SIZE; i++)
	{
		if (tmp_map[0][i] == 2)      flood_fill_from_edge(tmp_map, EDITED_MAP_GRID_SIZE, i, 0, 3);
		if (tmp_map[EDITED_MAP_GRID_SIZE-1][i] == 2) flood_fill_from_edge(tmp_map, EDITED_MAP_GRID_SIZE, i, EDITED_MAP_GRID_SIZE-1, 3);
		if (tmp_map[i][0] == 2)      flood_fill_from_edge(tmp_map, EDITED_MAP_GRID_SIZE, 0, i, 3);
		if (tmp_map[i][EDITED_MAP_GRID_SIZE-1] == 2) flood_fill_from_edge(tmp_map, EDITED_MAP_GRID_SIZE, EDITED_MAP_GRID_SIZE-1, i, 3);
	}
	for (int i = 0; i < EDITED_MAP_GRID_SIZE; i++)
	{
		for (int j = 0; j < EDITED_MAP_GRID_SIZE; j++)
		{
			if (gen->edited_map[i][j] == 2 && tmp_map[i][j] == 2)
				gen->edited_map[i][j] = 0;
		}
		free(tmp_map[i]);
	}
	free(tmp_map);
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
	fill_playable_spaces(gen);
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
			for (int j = 0; j < EDITED_MAP_GRID_SIZE; j++)
			{
				for (int k = 0; k < EDITED_MAP_GRID_SIZE; k++)
				{
					int val = gen->edited_map[j][k];
					if (val == 2)
					{
						ft_putstr_fd(" ", fd);
						continue ;
					}
					char *cell_str = ft_itoa(val);
					ft_putstr_fd(cell_str, fd);
					free(cell_str);
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

void	update_edited_map(int edited_map[EDITED_MAP_GRID_SIZE][EDITED_MAP_GRID_SIZE], int x, int y)
{
	if (edited_map[y][x] == 2)
		edited_map[y][x] = 1;
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
