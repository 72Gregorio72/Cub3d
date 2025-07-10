/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:42:14 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 16:16:20 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	unclosed_zero(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (map->map_matrix[i][j])
		{
			if (map->map_matrix[i][j] == '0')
			{
				if (i == 0 || i == map->height - 1
					|| j == 0 || !map->map_matrix[i][j + 1]
					|| j >= (int)ft_strlen(map->map_matrix[i - 1])
					|| j >= (int)ft_strlen(map->map_matrix[i + 1])
					|| map->map_matrix[i + 1][j] == '2'
					|| map->map_matrix[i - 1][j] == '2'
					|| map->map_matrix[i][j + 1] == '2'
					|| map->map_matrix[i][j - 1] == '2')
					return (0);
			}
			j++;
		}
	}
	return (1);
}

void	ft_lstclear_proj(t_projectile **stackA)
{
	t_projectile	*temp;

	temp = NULL;
	while (*stackA)
	{
		temp = (*stackA)->next;
		free(*stackA);
		*stackA = NULL;
		if (temp == NULL)
			break ;
		*stackA = temp;
	}
}

int	unclosed_door(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (map->map_matrix[i][j])
		{
			if (map->map_matrix[i][j] == 'D')
			{
				if (i == 0 || i == map->height - 1
					|| j == 0 || !map->map_matrix[i][j + 1]
					|| j >= (int)ft_strlen(map->map_matrix[i - 1])
					|| j >= (int)ft_strlen(map->map_matrix[i + 1])
					|| map->map_matrix[i + 1][j] == '2'
					|| map->map_matrix[i - 1][j] == '2'
					|| map->map_matrix[i][j + 1] == '2'
					|| map->map_matrix[i][j - 1] == '2')
					return (0);
			}
			j++;
		}
	}
	return (1);
}

void	create_map_file(t_gen *gen)
{
	int		fd;
	char	*map_path;

	map_path = ft_strjoin("ciao", ".cub");
	if (!map_path)
		return ;
	fd = open(map_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(map_path);
		return ;
	}
	for (int i = 0; i < gen->map.height; i++)
	{
		ft_putstr_fd(gen->map.map_matrix[i], fd);
		write(fd, "\n", 1);
	}
	close(fd);
	free(map_path);
}

void	util_close_window(t_gen *gen)
{
	if (gen->door.door_closed.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->door.door_closed.img_ptr);
	if (gen->btn_exit_game.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_exit_game.img_ptr);
	if (gen->btn_map_selection.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_map_selection.img_ptr);
	if (gen->btn_start_game.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_start_game.img_ptr);
	if (gen->btn_options.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_options.img_ptr);
	if (gen->btn_back_home.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_back_home.img_ptr);
	create_map_file(gen);
}

void	free_all_buttons(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->map_button_count)
	{
		if (gen->map_buttons[i].filepath)
			free(gen->map_buttons[i].filepath);
		i++;
	}
	free(gen->map_buttons);
}
