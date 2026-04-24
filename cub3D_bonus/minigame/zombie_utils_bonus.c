/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:32:00 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/04 16:40:15 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	add_zombie(t_gen *gen, double x, double y)
{
	t_zombie	*new_zombie;

	new_zombie = malloc(sizeof(t_zombie));
	if (!new_zombie)
		return ;
	new_zombie->x = x + 0.5;
	new_zombie->y = y + 0.5;
	new_zombie->health = 100;
	new_zombie->max_health = 100;
	new_zombie->attack_power = 10;
	new_zombie->attacked = 0;
	new_zombie->last_attack_time = 0;
	new_zombie->next = NULL;
	new_zombie->next = gen->zombies;
	gen->zombies = new_zombie;
	new_zombie->sprite_index = 0;
	new_zombie->is_dead = 0;
	new_zombie->is_walking = 1;
	new_zombie->is_attacking = 0;
	new_zombie->is_hit = 0;
	new_zombie->animation_frame = 0;
	new_zombie->texture = gen->zombie_tex_walking[0];
	gen->num_zombies++;
}

void	remove_zombie(t_gen *gen, t_zombie *zombie_to_remove)
{
	t_zombie	**ptr;
	t_zombie	*tmp;

	gen->map.map_matrix[(int)zombie_to_remove->y]
	[(int)zombie_to_remove->x] = '0';
	ptr = &gen->zombies;
	tmp = *ptr;
	while (*ptr && *ptr != zombie_to_remove)
		ptr = &(*ptr)->next;
	if (*ptr)
	{
		tmp = *ptr;
		*ptr = tmp->next;
		free(tmp);
		gen->num_zombies--;
	}
}

void	update_matrix_zombie(int old_x, int old_y, t_zombie *zombie, t_gen *gen)
{
	int	new_x;
	int	new_y;

	if (old_y >= 0 && old_y < gen->map.height
		&& old_x >= 0 && old_x < gen->map.width)
	{
		if (gen->map.map_matrix[old_y][old_x] == 'D')
			return ;
		gen->map.map_matrix[old_y][old_x] = '0';
	}
	new_x = (int)zombie->x;
	new_y = (int)zombie->y;
	if (new_y >= 0 && new_y < gen->map.height
		&& new_x >= 0 && new_x < gen->map.width)
	{
		if (gen->map.map_matrix[new_y][new_x] == 'D')
			return ;
		gen->map.map_matrix[new_y][new_x] = 'Z';
	}
}

void	util_move_zombie(t_draw_data *d, t_zombie *z, t_gen *gen)
{
	d->step_x = d->dx / d->dist * ZOMBIE_SPEED;
	d->step_y = d->dy / d->dist * ZOMBIE_SPEED;
	d->next_x = z->x + d->step_x;
	d->next_y = z->y + d->step_y;
	if (d->next_x < 0)
		d->next_x = 0;
	else if (d->next_x >= gen->map.width)
		d->next_x = gen->map.width - 1;
	if (d->next_y < 0)
		d->next_y = 0;
	else if (d->next_y >= gen->map.height)
		d->next_y = gen->map.height - 1;
}

void	move_zombie(t_gen *gen, t_zombie *z, t_draw_data d)
{
	int		old_x;
	int		old_y;

	old_x = (int)z->x;
	old_y = (int)z->y;
	if (z->is_dead && z->is_hit)
		return ;
	if (d.dist > 0.4)
	{
		util_move_zombie(&d, z, gen);
		if (gen->map.map_matrix[(int)z->y][(int)d.next_x] != '1'
			&& gen->map.map_matrix[(int)z->y][(int)d.next_x] != 'D')
			z->x = d.next_x;
		if (gen->map.map_matrix[(int)d.next_y][(int)z->x] != '1'
			&& gen->map.map_matrix[(int)d.next_y][(int)z->x] != 'D')
			z->y = d.next_y;
	}
	else
		z->is_walking = 0;
	if (old_x != (int)z->x || old_y != (int)z->y)
		update_matrix_zombie(old_x, old_y, z, gen);
}
