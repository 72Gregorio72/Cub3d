/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:52:58 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/23 11:23:40 by vcastald         ###   ########.fr       */
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

void	util_start(t_gen *g, int flag, char **start)
{
	if (flag)
		*start = ft_substr(g->map.f_tex,
				get_char_pos(g->map.f_tex, ' ') + 1, ft_strlen(g->map.f_tex));
	else
		*start = ft_substr(g->map.c_tex,
				get_char_pos(g->map.c_tex, ' ') + 1, ft_strlen(g->map.c_tex));
}

int	fill_colors(t_gen *g, int flag)
{
	char	*start;
	char	**tmp;
	int		i;
	int		j;

	start = NULL;
	util_start(g, flag, &start);
	tmp = ft_split(start, ',');
	i = -1;
	while (++i < 3)
	{
		j = -1;
		if (!ft_isdigit(tmp[i][++j]))
			return (printf(RED"Error: wrong rgb!\n"RESET),
				free(start), free_matrix(tmp, 3), 0);
		if (flag)
			g->map.floor_color[i] = ft_atoi(tmp[i]);
		else
			g->map.ceil_color[i] = ft_atoi(tmp[i]);
	}
	if (!check_rgb(g))
		return (free(start), free_matrix(tmp, 3), 0);
	return (free(start), free_matrix(tmp, 3), 1);
}

int	check_textures(t_gen *gen)
{
	int	fd;

	clean_path(gen->map.n_tex);
	clean_path(gen->map.s_tex);
	clean_path(gen->map.w_tex);
	clean_path(gen->map.e_tex);
	fd = open(gen->map.n_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong NO texture path!\n"RESET), 0);
	close(fd);
	fd = open(gen->map.s_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong SO texture path!\n"RESET), 0);
	close(fd);
	fd = open(gen->map.w_tex, O_RDONLY);
	if (fd < 0)
		return (printf(RED"Error: wrong WE texture path!\n"RESET), 0);
	close(fd);
	fd = open(gen->map.e_tex, O_RDONLY);
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
