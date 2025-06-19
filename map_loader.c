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

char	*get_texture_paths(char *file, t_gen *gen)
{
	char	*line;
	int		fd;
	int		found;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	found = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!ft_strncmp(line, "NO", 2))
			gen->map.N_tex = get_path(line);
		else if (!ft_strncmp(line, "SO", 2))
			gen->map.S_tex = get_path(line);
		else if (!ft_strncmp(line, "WE", 2))
			gen->map.W_tex = get_path(line);
		else if (!ft_strncmp(line, "EA", 2))
			gen->map.E_tex = get_path(line);
		else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			continue; // Handle floor and ceiling colors later
		else
			continue;
		free(line);
	}
	close(fd);
	if (!found)
		return (NULL);
	return (get_path(line));
}

void    read_map(char **av, t_gen *gen)
{
	get_texture_paths(av[1], gen);
	printf(YELLOW);
	printf("North texture: %s\n", gen->map.N_tex);
	printf("South texture: %s\n", gen->map.S_tex);
	printf("West texture: %s\n", gen->map.W_tex);
	printf("East texture: %s\n", gen->map.E_tex);
	printf(RESET);
}
