/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:17:11 by marvin            #+#    #+#             */
/*   Updated: 2025/06/19 19:17:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n' || line[i] == '\r')
		return (0);
	if (!ft_strncmp(&line[i], "NO", 2)
		|| !ft_strncmp(&line[i], "SO", 2)
		|| !ft_strncmp(&line[i], "WE", 2)
		|| !ft_strncmp(&line[i], "EA", 2)
		|| !ft_strncmp(&line[i], "F", 1)
		|| !ft_strncmp(&line[i], "C", 1))
		return (0);
	return (1);
}

static int	util_get_dimensions(int *width, int *height, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	*width = 0;
	*height = 0;
	return (fd);
}

void	get_map_dimensions(char *file, t_map *map)
{
	char	*line;
	int		fd;
	int		width;
	int		height;
	int		len;

	fd = util_get_dimensions(&width, &height, file);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line))
		{
			len = ft_strlen(line);
			if (len > 1 && line[len - 1] == '\n')
				len--;
			if (len > width)
				width = len;
			height++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->width = width;
	map->height = height;
}

static int	is_map_content_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	if (!ft_strncmp(&line[i], "NO", 2)
		|| !ft_strncmp(&line[i], "SO", 2)
		|| !ft_strncmp(&line[i], "WE", 2)
		|| !ft_strncmp(&line[i], "EA", 2)
		|| !ft_strncmp(&line[i], "F", 1)
		|| !ft_strncmp(&line[i], "C", 1)
		|| line[i] == '\n'
		|| line[i] == '\r')
		return (0);
	return (1);
}

void	read_file(int fd, int i, t_gen *gen, int y)
{
	char	*line;

	i++;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_content_line(line))
		{
			fill_map_row(gen, line, y);
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

//print_map(gen);
/*printf(YELLOW);
printf("North texture: %s\n", gen->map.n_tex);
printf("South texture: %s\n", gen->map.s_tex);
printf("West texture: %s\n", gen->map.w_tex);
printf("East texture: %s\n", gen->map.e_tex);
printf("Floor texture: %s\n", gen->map.f_tex);
printf("Ceiling texture: %s\n", gen->map.c_tex);*/