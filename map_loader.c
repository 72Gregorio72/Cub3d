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

void	get_map_dimensions(char *file, t_map *map)
{
	char	*line;
	int		fd;
	int		width = 0;
	int		height = 0;
	int		len;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while ((line = get_next_line(fd)) != NULL)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!(line[i] == '\0' || line[i] == '\n' || line[i] == '\r')
			&& !((!ft_strncmp(&line[i], "NO", 2) || !ft_strncmp(&line[i], "SO", 2)
			|| !ft_strncmp(&line[i], "WE", 2) || !ft_strncmp(&line[i], "EA", 2)
			|| !ft_strncmp(&line[i], "F", 1)  || !ft_strncmp(&line[i], "C", 1))))
		{
			i = 0;
			len = ft_strlen(&line[i]) - 2;
			if (len > 0 && line[i + len - 1] == '\n')
				len--;
			if (len > width)
				width = len;
			height++;
		}
		free(line);
	}
	close(fd);
	map->width = width;
	map->height = height;
}

void	read_file(int fd, int i, t_gen *gen, int y)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] && ft_strncmp(&line[i], "NO", 2) && ft_strncmp(&line[i], "SO", 2)
			&& ft_strncmp(&line[i], "WE", 2) && ft_strncmp(&line[i], "EA", 2)
			&& ft_strncmp(&line[i], "F", 1) && ft_strncmp(&line[i], "C", 1)
			&& line[i] != '\n' && line[i] != '\r')
		{
			i = 0;
			while (line[i] && line[i] != '\n' && line[i] != '\r' && i < gen->map.width)
			{
				if (line[i] == ' ' || line[i] == '\t')
					gen->map.map_matrix[y][i] = '2';
				else
					gen->map.map_matrix[y][i] = line[i];
				i++;
			}
			while (i < gen->map.width)
				gen->map.map_matrix[y][i++] = '2';
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	load_map(char **av, t_gen *gen)
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
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return ;
	read_file(fd, i, gen, y);
	close(fd);
}

void	print_map(t_gen *gen)
{
	int i;
	int	j;

	i = 0;
	while (i < gen->map.height)
	{
		j = 0;
		while (j < gen->map.width)
		{
			if (gen->map.map_matrix[i][j] == '2')
				printf(" ");
			else if (gen->map.map_matrix[i][j] == '1' || gen->map.map_matrix[i][j] == '0')
				printf(RED"%c"RESET, gen->map.map_matrix[i][j]);
			else if (gen->map.map_matrix[i][j] == 'N')
				printf(BLUE"%c"RESET, gen->map.map_matrix[i][j]);
			else
				printf("%c", gen->map.map_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int    read_map(char **av, t_gen *gen)
{
	if (!get_texture_paths(av[1], gen))
		return (0);
	printf(YELLOW);
	printf("North texture: %s\n", gen->map.N_tex);
	printf("South texture: %s\n", gen->map.S_tex);
	printf("West texture: %s\n", gen->map.W_tex);
	printf("East texture: %s\n", gen->map.E_tex);
	printf("Floor texture: %s\n", gen->map.F_tex);
	printf("Ceiling texture: %s\n", gen->map.C_tex);
	get_map_dimensions(av[1], &gen->map);
	load_map(av, gen);
	print_map(gen);
	set_player_position(gen);
	gen->map.floor_color = ft_calloc(3, sizeof(int));
	gen->map.ceil_color = ft_calloc(3, sizeof(int));
	return (1);
}
