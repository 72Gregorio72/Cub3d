/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_loader.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:48:56 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/20 15:04:21 by vcastald         ###   ########.fr       */
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

void	init_textures(t_gen *gen)
{
	gen->map.N_tex = NULL;
	gen->map.S_tex = NULL;
	gen->map.W_tex = NULL;
	gen->map.E_tex = NULL;
	gen->map.F_tex = NULL;
	gen->map.C_tex = NULL;
}

int	fill_textures(t_gen *gen, char *line)
{
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
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		original = line;
		while (*line && ((*line == ' ') || (*line == '\t')))
			line++;
		if (!fill_textures(gen, line))
			return (0);
		free(original);
	}
	if (!gen->map.N_tex || !gen->map.S_tex || !gen->map.W_tex
		|| !gen->map.E_tex || !gen->map.F_tex || !gen->map.C_tex)
		return (printf(RED"Error: missing texture!\n"RESET), free_gen(gen, 0), 0);
	close(fd);
	return (1);
}

int	get_char_pos(char *src, int c)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
