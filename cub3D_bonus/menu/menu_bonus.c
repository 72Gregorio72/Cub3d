/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:52:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/30 16:37:01 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <dirent.h>

#define MAPS_PER_ROW 3
#define MAP_BOX_W 250
#define MAP_BOX_H 50
#define START_X 100
#define START_Y 150

static char	**get_map_files(int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	dir = opendir("maps");
	if (!dir)
		return (NULL);
	files = malloc(sizeof(char *) * 100);
	if (!files)
		return (NULL);
	i = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_type == 8
			&& ft_strnstr(entry->d_name, ".cub", ft_strlen(entry->d_name)))
			files[i++] = ft_strjoin("maps/", entry->d_name);
	}
	files[i] = NULL;
	*count = i;
	closedir(dir);
	return (files);
}

void	load_map1(char *path, t_gen *gen)
{
	int		fd;
	int		y;
	int		i;

	i = 0;
	y = 0;
	gen->map.map_matrix = malloc(sizeof(char *) * gen->map.height);
	if (!gen->map.map_matrix)
		return ;
	while (i < gen->map.height)
	{
		gen->map.map_matrix[i] = ft_calloc(gen->map.width + 1, sizeof(char));
		if (!gen->map.map_matrix[i])
			return ;
		i++;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	read_file(fd, i, gen, y);
	close(fd);
}

void	free_gen_map(t_gen *gen)
{
	int	i;

	if (gen->map.map_matrix)
	{
		i = 0;
		while (i < gen->map.height)
		{
			free(gen->map.map_matrix[i]);
			i++;
		}
		free(gen->map.map_matrix);
		gen->map.map_matrix = NULL;
	}
	if (gen->map.floor_color)
		free(gen->map.floor_color);
	if (gen->map.ceil_color)
		free(gen->map.ceil_color);
	gen->map.floor_color = NULL;
	gen->map.ceil_color = NULL;
	if (gen->map.n_tex)
		free(gen->map.n_tex);
	if (gen->map.s_tex)
		free(gen->map.s_tex);
	if (gen->map.w_tex)
		free(gen->map.w_tex);
	if (gen->map.e_tex)
		free(gen->map.e_tex);
}

int	get_map(char *path, t_gen *gen)
{
	free_gen_map(gen);
	gen->map.floor_color = ft_calloc(3, sizeof(int));
	gen->map.ceil_color = ft_calloc(3, sizeof(int));
	if (!get_texture_paths(path, gen))
		return (0);
	get_map_dimensions(path, &gen->map);
	load_map1(path, gen);
	set_player_position(gen);
	if (!parsing_map(gen))
	{
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 50, 50,
			0xFF0000, "Error parsing map");
		return (0);
	}
	return (1);
}

void	draw_map_preview(t_gen *gen, int x, int y, int width, int height)
{
	int		i;
	int		j;
	int		color;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i < gen->map.height && j < gen->map.width)
			{
				if (gen->map.map_matrix[i][j] == '1')
					color = 0xFFFFFF;
				else if (gen->map.map_matrix[i][j] == '0')
					color = 0x000000;
				else
					color = 0xFF0000;
			}
			int bx, by;
			for (by = 0; by < 5; by++)
			{
				for (bx = 0; bx < 5; bx++)
				{
					put_pixel(&gen->img, x + j * 5 + bx, y + i * 5 + by, color);
				}
			}
		}
	}
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
}

void	draw_map_selector(t_gen *gen)
{
	int		i;
	int		count;
	int		x, y;
	int		row, col;
	char	**map_files;
	char	*filename;

	map_files = get_map_files(&count);
	if (!map_files || count == 0)
	{
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 50, 50,
			0xFF0000, "No map files found in /maps");
		return ;
	}
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2 - 80, 80,
		0xFFFFFF, "Select a map:");
	i = 0;
	while (i < count)
	{
		row = i / MAPS_PER_ROW;
		col = i % MAPS_PER_ROW;
		x = START_X + col * MAP_BOX_W;
		y = START_Y + row * MAP_BOX_H;
		filename = map_files[i] + 5;
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, x, y, 0x00FFCC, filename);
		get_map(map_files[i], gen);
		draw_map_preview(gen, x, y, gen->map.width, gen->map.height);
		free(map_files[i]);
		i++;
	}
	free(map_files);
}

void	draw_menu(t_gen *gen)
{
	int		x;
	int		y;
	char	*title;
	char	*option1;
	char	*option2;

	title = "CUB3D BONUS";
	option1 = "W - Start Game";
	option2 = "Q - Quit";
	x = (SCREEN_X - ft_strlen(title) * 10) / 2;
	y = SCREEN_Y / 2 - 40;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, x, y, 0xFFFFFF, title);

	x = (SCREEN_X - ft_strlen(option1) * 10) / 2;
	y += 40;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, x, y, 0x00FF00, option1);

	x = (SCREEN_X - ft_strlen(option2) * 10) / 2;
	y += 30;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, x, y, 0xFF0000, option2);
	draw_map_selector(gen);
}
