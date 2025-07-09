/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_check_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:55:08 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 10:28:46 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	util_map_check(t_gen *gen, int i, int j)
{
	if (gen->map.map_matrix[i][j] != 'N'
	&& gen->map.map_matrix[i][j] != '0'
	&& gen->map.map_matrix[i][j] != '1'
	&& gen->map.map_matrix[i][j] != '2'
	&& gen->map.map_matrix[i][j] != 'S'
	&& gen->map.map_matrix[i][j] != 'W'
	&& gen->map.map_matrix[i][j] != 'E'
	&& gen->map.map_matrix[i][j] != 'Z'
	&& gen->map.map_matrix[i][j] != 'D')
		return (1);
	return (0);
}

int	map_check(t_gen *gen)
{
	int	i;
	int	j;
	int	count_n;

	i = 0;
	count_n = 0;
	while (i < gen->map.height)
	{
		j = -1;
		while (gen->map.map_matrix[i][++j])
		{
			if (util_map_check(gen, i, j))
				return (printf(RED"Error\n wrong map!\n"RESET), 0);
			if (gen->map.map_matrix[i][j] == 'N'
				|| gen->map.map_matrix[i][j] == 'S'
				|| gen->map.map_matrix[i][j] == 'E'
				|| gen->map.map_matrix[i][j] == 'W')
				count_n++;
		}
		i++;
	}
	if (count_n != 1)
		return (
			printf(RED"Error\n wrong number of starting positions!\n"RESET), 0);
	return (1);
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

/* void	print_map(t_gen *gen)
{
	int	i;
	int	j;

	i = -1;
	while (++i < gen->map.height)
	{
		j = 0;
		while (j < gen->map.width)
		{
			if (gen->map.map_matrix[i][j] == '2')
				printf(" ");
			else if (gen->map.map_matrix[i][j] == '1'
				|| gen->map.map_matrix[i][j] == '0')
				printf(RED"%c"RESET, gen->map.map_matrix[i][j]);
			else if (gen->map.map_matrix[i][j] == 'N'
					|| gen->map.map_matrix[i][j] == 'S'
					|| gen->map.map_matrix[i][j] == 'E'
					|| gen->map.map_matrix[i][j] == 'W')
				printf(BLUE"%c"RESET, gen->map.map_matrix[i][j]);
			else
				printf("%c", gen->map.map_matrix[i][j]);
			j++;
		}
		printf("\n");
	}
} */

int	read_map(char **av, t_gen *gen)
{
	gen->map.floor_color = ft_calloc(3, sizeof(int));
	gen->map.ceil_color = ft_calloc(3, sizeof(int));
	if (!get_texture_paths(av[1], gen))
		return (0);
	get_map_dimensions(av[1], &gen->map);
	load_map(av, gen);
	set_player_position(gen);
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
