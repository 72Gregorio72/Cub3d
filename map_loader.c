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

char	*get_path(char *line)
{
	char	*path;
	int		i;

	i = 0;
	line = line + 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (NULL);
	path = ft_strdup(&line[i]);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '\n')
		i++;
	path[i] = '\0';
	return (path);
}

void	get_texture_paths(char *file, t_gen *gen)
{
	char	*line;
	char	*original;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		original = line;
		while (*line && ((*line == ' ') || (*line == '\t')))
			line++;
		if (!ft_strncmp(line, "NO", 2))
			gen->map.N_tex = get_path(line);
		else if (!ft_strncmp(line, "SO", 2))
			gen->map.S_tex = get_path(line);
		else if (!ft_strncmp(line, "WE", 2))
			gen->map.W_tex = get_path(line);
		else if (!ft_strncmp(line, "EA", 2))
			gen->map.E_tex = get_path(line);
		else if (!ft_strncmp(line, "F", 1))
			gen->map.F_tex = get_path(line);
		else if (!ft_strncmp(line, "C", 1))
			gen->map.C_tex = get_path(line);
		free(original);
	}
	close(fd);
}

void	get_map_dimensions(char *file, t_map *map)
{
	char	*line;
	char	*original;
	int		fd;
	int		width = 0;
	int		height = 0;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while ((line = get_next_line(fd)) != NULL)
	{
		original = line;
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0' || *line == '\n' || *line == '\r')
		{
			printf("Empty line found, skipping...\n");
			free(original);
		}
		else
		{
			if (!*line || !ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
				|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
				|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			{
				free(original);
				continue;
			}
			len = ft_strlen(line) - 2;
			if (len > width)
				width = len;
			height++;
			free(original);
		}
	}
	close(fd);
	map->width = width;
	map->height = height;
}

void	load_map(char **av, t_gen *gen)
{
	char	*line;
	char	*original;
	int		fd;
	int		y = 0;

	gen->map.map_matrix = malloc(sizeof(char *) * gen->map.height);
	if (!gen->map.map_matrix)
	{
		perror("malloc map_matrix");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < gen->map.height; i++)
	{
		gen->map.map_matrix[i] = ft_calloc(gen->map.width + 1, sizeof(char));
		if (!gen->map.map_matrix[i])
		{
			perror("calloc row");
			exit(EXIT_FAILURE);
		}
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL && y < gen->map.height)
	{
		original = line;
		while (*line == ' ' || *line == '\t')
			line++;

		if (!*line || !ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
			|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		{
			free(original);
			continue;
		}
		int i = 0;
		while (line[i] && line[i] != '\n' && i < gen->map.width)
		{
			if (line[i] == ' ' || line[i] == '\t')
				gen->map.map_matrix[y][i] = '0';
			else
				gen->map.map_matrix[y][i] = line[i];
			i++;
		}
		while (i < gen->map.width)
			gen->map.map_matrix[y][i++] = '0';

		y++;
		free(original);
	}
	close(fd);
}

void    read_map(char **av, t_gen *gen)
{
	get_texture_paths(av[1], gen);
	printf(YELLOW);
	printf("North texture: %s\n", gen->map.N_tex);
	printf("South texture: %s\n", gen->map.S_tex);
	printf("West texture: %s\n", gen->map.W_tex);
	printf("East texture: %s\n", gen->map.E_tex);
	printf("Floor texture: %s\n", gen->map.F_tex);
	printf("Ceiling texture: %s\n", gen->map.C_tex);
	get_map_dimensions(av[1], &gen->map);
	load_map(av, gen);
	printf(RED);
	for (int i = 0; i < gen->map.height; i++)
		printf("%s\n", gen->map.map_matrix[i]);
	printf(RESET);
}
