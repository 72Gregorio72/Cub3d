/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:08:02 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/25 11:08:02 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cleanup_projectiles(t_gen *gen)
{
	t_projectile	**curr;
	t_projectile	*tmp;

	curr = &gen->projectiles;
	while (*curr)
	{
		if (!(*curr)->active)
		{
			tmp = *curr;
			*curr = tmp->next;
			free(tmp);
		}
		else
			curr = &(*curr)->next;
	}
}

void	add_projectile(t_gen *gen)
{
	t_projectile	*new_proj;

	new_proj = malloc(sizeof(t_projectile));
	if (!new_proj)
		return ;
	new_proj->x = gen->player.x;
	new_proj->y = gen->player.y;
	new_proj->dir_x = gen->player.dir_x;
	new_proj->dir_y = gen->player.dir_y;
	new_proj->damage = 20;
	new_proj->active = 1;
	new_proj->next = gen->projectiles;
	gen->projectiles = new_proj;
}

void	check_draw(t_gen *gen, double next_x, double next_y, t_projectile *curr)
{
	int	map_x = (int)next_x;
	int	map_y = (int)next_y;
	int	screen_xy[2];

	if (map_x < 0 || map_y < 0 ||
		map_y >= gen->map.height ||
		map_x >= gen->map.width ||
		!gen->map.map_matrix[map_y])
	{
		curr->active = 0;
		return ;
	}

	if (gen->map.map_matrix[map_y][map_x] == '1')
		curr->active = 0;
	else
	{
		curr->x = next_x;
		curr->y = next_y;
		screen_xy[0] = SCREEN_X / 2;
		screen_xy[1] = SCREEN_Y / 2;
		put_pixel(&gen->img, screen_xy[0], screen_xy[1], 0xFF0000);
	}
}

void	update_projectile_position(t_gen *gen)
{
	t_projectile	*curr;
	t_projectile	*prev;
	double			next_x;
	double			next_y;

	prev = NULL;
	curr = gen->projectiles;
	while (curr)
	{
		if (!curr->active)
		{
			prev = curr;
			curr = curr->next;
			continue ;
		}
		next_x = curr->x + curr->dir_x * MOVE_SPEED;
		next_y = curr->y + curr->dir_y * MOVE_SPEED;
		check_draw(gen, next_x, next_y, curr);
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		return ;
}
