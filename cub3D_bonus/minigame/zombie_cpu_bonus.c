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

void	draw_zombie_column(t_gen *gen, int screen_x, int draw_start, int draw_end)
{
	int		y;
	int		x_offset;
	int		width = 10;

	for (x_offset = -width / 2; x_offset <= width / 2; x_offset++)
	{
		int x = screen_x + x_offset;
		if (x < 0 || x >= SCREEN_X)
			continue ;
		y = draw_start;
		while (y < draw_end)
		{
			put_pixel(&gen->img, x, y, 0x00FF00);
			y++;
		}
	}
}

size_t    get_current_time(void)
{
    struct timeval    time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	damage_player(t_zombie *z)
{
	z->attacked = 1;
	z->last_attack_time = get_current_time();
	printf(RED"Player damaged by zombie at position (%.2f, %.2f)!\n"RESET,
		z->x, z->y);
}

void	check_zombie_hits(t_gen *gen)
{
	t_zombie *z = gen->zombies;
	t_zombie *next;

	while (z)
	{
		next = z->next;
		if (gen->projectiles.active)
		{
			double dx = gen->projectiles.x - z->x;
			double dy = gen->projectiles.y - z->y;
			double dist = sqrt(dx * dx + dy * dy);
			if (dist < 0.5)
			{
				printf(GREEN"Zombie at (%.2f, %.2f) hit and removed\n"RESET, z->x, z->y);
				remove_zombie(gen, z);
			}
		}
		z = next;
	}
}

void	add_zombie(t_gen *gen, double x, double y)
{
    t_zombie *new_zombie;

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
    gen->num_zombies++;
}

void	remove_zombie(t_gen *gen, t_zombie *zombie_to_remove)
{
	t_zombie **ptr = &gen->zombies;
	while (*ptr && *ptr != zombie_to_remove)
		ptr = &(*ptr)->next;

	if (*ptr)
	{
		t_zombie *tmp = *ptr;
		*ptr = tmp->next;
		free(tmp);
		gen->num_zombies--;
	}
}

void	update_zombies_position(t_gen *gen)
{
	t_zombie *z = gen->zombies;
	double dx, dy, dist, step_x, step_y, next_x, next_y;
	size_t now = get_current_time();

	printf("zombie number: %d\n", gen->num_zombies);
	while (z)
	{
		if (now - z->last_attack_time > 1000)
			z->attacked = 0;

		dx = gen->player.x - z->x;
		dy = gen->player.y - z->y;
		dist = sqrt(dx * dx + dy * dy);
		if (dist > 0.1)
		{
			step_x = dx / dist * ZOMBIE_SPEED;
			step_y = dy / dist * ZOMBIE_SPEED;
			next_x = z->x + step_x;
			next_y = z->y + step_y;

			if (gen->map.map_matrix[(int)z->y][(int)next_x] != '1')
				z->x = next_x;
			if (gen->map.map_matrix[(int)next_y][(int)z->x] != '1')
				z->y = next_y;
		}
		if (dist < 0.2 && !z->attacked)
			damage_player(z);
		z = z->next;
	}
}
