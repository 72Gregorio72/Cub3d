/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie_cpu_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:08:07 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/25 11:08:07 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ZOMBIE_SPEED 0.01

size_t    get_current_time(void)
{
    struct timeval    time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	damage_player(t_gen *gen, int zombie_index)
{
	gen->zombies[zombie_index].attacked = 1;
	gen->zombies[zombie_index].last_attack_time = get_current_time();
	printf(RED"Player damaged by zombie at position (%.2f, %.2f)!\n"RESET,
		gen->zombies[zombie_index].x, gen->zombies[zombie_index].y);
}

void	check_zombie_hit(t_gen *gen, int zombie_index)
{
	if (gen->projectiles.active)
	{
		double dx = gen->projectiles.x - gen->zombies[zombie_index].x;
		double dy = gen->projectiles.y - gen->zombies[zombie_index].y;
		double dist = sqrt(dx * dx + dy * dy);
		if (dist < 0.5)
		{
			printf(GREEN"Zombie at position (%.2f, %.2f) hit by projectile!\n"RESET,
				gen->zombies[zombie_index].x, gen->zombies[zombie_index].y);
		}
	}
}

void	update_zombies_position(t_gen *gen)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;
	double	step_x;
	double	step_y;
	double	next_x;
	double	next_y;
	struct	timeval now;

	gettimeofday(&now, NULL);
	i = 0;
	while (i < gen->num_zombies)
	{
		check_zombie_hit(gen, i);
		if (gen->zombies[i].last_attack_time - get_current_time() < (long unsigned int)-1000)
			gen->zombies[i].attacked = 0;
		dx = gen->player.x - gen->zombies[i].x;
		dy = gen->player.y - gen->zombies[i].y;
		dist = sqrt(dx * dx + dy * dy);
		if (dist > 0.1)
		{
			step_x = dx / dist * ZOMBIE_SPEED;
			step_y = dy / dist * ZOMBIE_SPEED;
			next_x = gen->zombies[i].x + step_x;
			next_y = gen->zombies[i].y + step_y;
			if (gen->map.map_matrix[(int)gen->zombies[i].y][(int)next_x] != '1')
				gen->zombies[i].x = next_x;
			if (gen->map.map_matrix[(int)next_y][(int)gen->zombies[i].x] != '1')
				gen->zombies[i].y = next_y;
		}
		if (dist < 0.2 && !gen->zombies[i].attacked)
			damage_player(gen, i);
		i++;
	}
}
