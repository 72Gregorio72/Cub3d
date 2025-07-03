/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:42:14 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/03 11:47:54 by gpicchio         ###   ########.fr       */
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

void	util_close_window(t_gen *gen)
{
	if (gen->door.door_closed.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->door.door_closed.img_ptr);
	if (gen->door.door_half_open.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->door.door_half_open.img_ptr);
	if (gen->door.door_open.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->door.door_open.img_ptr);
	if (gen->btn_exit_game.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_exit_game.img_ptr);
	if (gen->btn_map_selection.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_map_selection.img_ptr);
	if (gen->btn_start_game.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->btn_start_game.img_ptr);
}

int	close_window(t_gen *gen)
{
	if (gen->img.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->img.img_ptr);
	if (gen->map.north.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.north.img_ptr);
	if (gen->map.south.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.south.img_ptr);
	if (gen->map.east.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.east.img_ptr);
	if (gen->map.west.img_ptr)
		mlx_destroy_image(gen->mlx_ptr, gen->map.west.img_ptr);
	util_close_window(gen);
	destroy_zombie_tex(gen);
	if (gen->win_ptr)
		mlx_destroy_window(gen->mlx_ptr, gen->win_ptr);
	if (gen->mlx_ptr)
	{
		mlx_destroy_display(gen->mlx_ptr);
		free(gen->mlx_ptr);
	}
	ft_lstclear_proj(&gen->projectiles);
	free_gen(gen, 1);
	exit(EXIT_SUCCESS);
}
