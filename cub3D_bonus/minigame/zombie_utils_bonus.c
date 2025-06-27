/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:32:00 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/27 12:10:40 by marvin           ###   ########.fr       */
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
	printf(GREEN"Zombie hit and removed\n"RESET);
}

void	move_zombie(t_gen *gen, t_zombie *z, t_draw_data d)
{
	if (d.dist > 0.4)
	{
		d.step_x = d.dx / d.dist * ZOMBIE_SPEED;
		d.step_y = d.dy / d.dist * ZOMBIE_SPEED;
		d.next_x = z->x + d.step_x;
		d.next_y = z->y + d.step_y;
		if (gen->map.map_matrix[(int)z->y][(int)d.next_x] != '1')
			z->x = d.next_x;
		if (gen->map.map_matrix[(int)d.next_y][(int)z->x] != '1')
			z->y = d.next_y;
	}
	else
	{
		z->is_walking = 0;
	}
}

void	update_zombies_position(t_gen *gen)
{
	t_zombie	*z;
	t_draw_data	d;
	size_t		now;

	z = gen->zombies;
	now = get_current_time();
	while (z)
	{
		if (now - z->last_attack_time > 1000)
			z->attacked = 0;
		d.dx = gen->player.x - z->x;
		d.dy = gen->player.y - z->y;
		d.dist = sqrt(d.dx * d.dx + d.dy * d.dy);
		move_zombie(gen, z, d);
		if (d.dist <= 0.5 && !z->attacked)
			update_attacking(z);
		else if (!z->is_walking && d.dist > 0.5)
			update_walking(z);
		z = z->next;
	}
}
