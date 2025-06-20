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

void	load_map(char **av, t_gen *gen)
{
	char	*line;
	int		fd;
	int		y = 0;
	int		i;
	
	i = 0;
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
	while ((line = get_next_line(fd)) != NULL)
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
					gen->map.map_matrix[y][i] = '0';
				else
					gen->map.map_matrix[y][i] = line[i];
				i++;
			}
			while (i < gen->map.width)
				gen->map.map_matrix[y][i++] = '0';
			y++;
		}
		free(line);
	}
	close(fd);
}

void    read_map(char **av, t_gen *gen)
{
	int i;
	int	j;

	i = 0;
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
	gen->num_zombies = 0;
	while (i < gen->map.height)
	{
		j = 0;
		while (j < gen->map.width)
		{
			if (gen->map.map_matrix[i][j] == '0')
				printf(" ");
			else if (gen->map.map_matrix[i][j] == '1')
				printf(RED"%c"RESET, gen->map.map_matrix[i][j]);
			else if (gen->map.map_matrix[i][j] == 'N')
				printf(BLUE"%c"RESET, gen->map.map_matrix[i][j]);
			else
				printf("%c", gen->map.map_matrix[i][j]);
			
			if (gen->map.map_matrix[i][j] == 'Z')
			{
				if (gen->num_zombies < MAX_ZOMBIES)
				{
					gen->zombies[gen->num_zombies].x = j + 0.5;
					gen->zombies[gen->num_zombies].y = i + 0.5;
					gen->zombies[gen->num_zombies].max_health = 100;
					gen->zombies[gen->num_zombies].health = gen->zombies[gen->num_zombies].max_health;
					gen->zombies[gen->num_zombies].attack_power = 10;
					gen->zombies[gen->num_zombies].attacked = 0;
					gen->num_zombies++;
				}
			}
			j++;
		}
		printf("\n");
		i++;
	}
	set_player_position(gen);
	printf("player position: x = %.1f, y = %.1f\n",
		gen->player.x, gen->player.y);
	gen->map.floor_color = ft_calloc(3, sizeof(int));
    gen->map.ceil_color = ft_calloc(3, sizeof(int));
}
