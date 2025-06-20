/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:52:58 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/20 15:10:07 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_rgb(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(gen->map.floor_color[i] >= 0 && gen->map.floor_color[i] <= 255)
			|| !(gen->map.ceil_color[i] >= 0 && gen->map.ceil_color[i] <= 255))
			return (printf(RED"Error: no rgb colors!\n"RESET), 0);
		i++;
	}
	return (1);
}

int	fill_colors(t_gen *gen, int flag)
{
	char	*start;
	char	**tmp;
	int		i;

	if (flag)
		start = ft_substr(gen->map.F_tex,
			get_char_pos(gen->map.F_tex, ' ') + 1, ft_strlen(gen->map.F_tex));
	else
		start = ft_substr(gen->map.C_tex,
			get_char_pos(gen->map.C_tex, ' ') + 1, ft_strlen(gen->map.C_tex));
	tmp = ft_split(start, ',');
	i = 0;
	while (i < 3)
	{
		if (flag)
			gen->map.floor_color[i] = ft_atoi(tmp[i]);
		else
			gen->map.ceil_color[i] = ft_atoi(tmp[i]);
		i++;
	}
	free_matrix(tmp, 3);
	if (!check_rgb(gen))
		return (free(start), 0);
	free(start);
	return (1);
}
int	check_textures(t_gen *gen)
{
	int	fd;

	clean_path(gen->map.N_tex);
	clean_path(gen->map.S_tex);
	clean_path(gen->map.W_tex);
	clean_path(gen->map.E_tex);
	fd = open(gen->map.N_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong NO texture path!\n"RESET), 0);
	close(fd);
	fd = open(gen->map.S_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong SO texture path!\n"RESET), 0);
	close(fd);
	fd = open(gen->map.W_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong WE texture path!\n"RESET), 0);
	close(fd);
	fd = open(gen->map.E_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong EA texture path!\n"RESET), 0);
	close(fd);
	return (1);
}

int	parsing_map(t_gen *gen)
{
	if (!map_check(gen) || !fill_colors(gen, 1) || !fill_colors(gen, 0)
		|| !check_textures(gen))
		return (0);
	if (!check_closed(gen))
		return (printf(RED"Error: unclosed map!\n"RESET), 0);
	return (1);
}
