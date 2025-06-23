/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:53:20 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/23 12:03:54 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_invalid(char c)
{
	return (c == ' ' || c == '\0');
}

int	flood_fill(t_map *map, int y, int x, int **visited)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (visited[y][x])
		return (1);
	if (is_invalid(map->map_matrix[y][x]))
		return (0);
	if (map->map_matrix[y][x] == '1')
		return (1);
	visited[y][x] = 1;
	return (
		flood_fill(map, y + 1, x, visited)
		&& flood_fill(map, y - 1, x, visited)
		&& flood_fill(map, y, x + 1, visited)
		&& flood_fill(map, y, x - 1, visited)
	);
}

int	get_x(t_map *map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map_matrix[i][j] == c)
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

int	get_y(t_map *map, char c, int col)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->map_matrix[i][col] == c)
			break ;
		i++;
	}
	return (i);
}

int	check_closed(t_gen *gen)
{
	int	**visited;
	int	i;
	int	valid;
	int	px;
	int	py;

	valid = 0;
	i = -1;
	visited = malloc(sizeof(int *) * gen->map.height);
	while (++i < gen->map.height)
	{
		visited[i] = ft_calloc(gen->map.width, sizeof(int));
		if (!visited[i])
			return (0);
	}
	px = get_x(&gen->map, gen->player_orientation);
	py = get_y(&gen->map, gen->player_orientation, px);
	valid = flood_fill(&gen->map, py, px, visited);
	i = -1;
	while (++i < gen->map.height)
		free(visited[i]);
	if (!valid)
		return (free(visited), 0);
	return (free(visited), unclosed_zero(&gen->map));
}
