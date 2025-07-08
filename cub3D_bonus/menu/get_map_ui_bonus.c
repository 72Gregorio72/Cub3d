/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_ui_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:44:34 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/07 16:00:39 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**get_map_files(int *count)
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
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == 8
			&& ft_strnstr(entry->d_name, ".cub", ft_strlen(entry->d_name)))
			files[i++] = ft_strjoin("maps/", entry->d_name);
		entry = readdir(dir);
	}
	files[i] = NULL;
	*count = i;
	closedir(dir);
	return (files);
}

static void	load_map1(char *path, t_gen *gen)
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

void	free_gen_map_util(t_gen *gen)
{
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

void	free_gen_map(t_gen *gen)
{
	int	i;

	if (gen->map.map_matrix)
	{
		i = -1;
		while (++i < gen->map.height)
			free(gen->map.map_matrix[i]);
		free(gen->map.map_matrix);
		gen->map.map_matrix = NULL;
	}
	if (gen->map.floor_color)
		free(gen->map.floor_color);
	if (gen->map.ceil_color)
		free(gen->map.ceil_color);
	free_gen_map_util(gen);
	if (gen->map.c_tex)
		free(gen->map.c_tex);
	if (gen->map.f_tex)
		free(gen->map.f_tex);
}

int	get_map(char *path, t_gen *gen)
{
	free_gen_map(gen);
	if (gen->map.floor_color)
		free(gen->map.floor_color);
	if (gen->map.ceil_color)
		free(gen->map.ceil_color);
	if (gen->map.width > 0 || gen->map.height > 0)
	{
		gen->map.width = 0;
		gen->map.height = 0;
	}
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
