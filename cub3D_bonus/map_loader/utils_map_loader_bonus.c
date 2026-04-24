/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_loader_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:48:56 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/26 12:35:04 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	init_textures(t_gen *gen)
{
	gen->map.n_tex = NULL;
	gen->map.s_tex = NULL;
	gen->map.w_tex = NULL;
	gen->map.e_tex = NULL;
	gen->map.f_tex = NULL;
	gen->map.c_tex = NULL;
}

int	fill_textures(t_gen *gen, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		gen->map.n_tex = get_path(line);
	else if (!ft_strncmp(line, "SO", 2))
		gen->map.s_tex = get_path(line);
	else if (!ft_strncmp(line, "WE", 2))
		gen->map.w_tex = get_path(line);
	else if (!ft_strncmp(line, "EA", 2))
		gen->map.e_tex = get_path(line);
	else if (!ft_strncmp(line, "F", 1))
		gen->map.f_tex = get_path(line);
	else if (!ft_strncmp(line, "C", 1))
		gen->map.c_tex = get_path(line);
	return (1);
}

int	get_texture_paths(char *file, t_gen *gen)
{
	char	*line;
	char	*original;
	int		fd;

	init_textures(gen);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit(EXIT_FAILURE), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		original = line;
		while (*line && ((*line == ' ') || (*line == '\t')))
			line++;
		if (!fill_textures(gen, line))
			return (0);
		free(original);
		line = get_next_line(fd);
	}
	if (!gen->map.n_tex || !gen->map.s_tex || !gen->map.w_tex
		|| !gen->map.e_tex || !gen->map.f_tex || !gen->map.c_tex)
		return (
			printf(RED"Error\n missing texture!\n"RESET), free_gen(gen, 0), 0);
	close(fd);
	return (1);
}
