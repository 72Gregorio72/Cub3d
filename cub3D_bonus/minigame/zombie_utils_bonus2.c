/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie_utils_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:49:18 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 15:51:36 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_zombie_hits(t_gen *gen)
{
	t_zombie		*z;
	t_zombie		*next_z;
	t_projectile	*proj;
	t_projectile	*p;
	t_draw_data		d;

	ft_memset(&d, 0, sizeof(t_draw_data));
	z = gen->zombies;
	proj = gen->projectiles;
	while (z)
	{
		next_z = z->next;
		p = proj;
		while (p)
		{
			if (!z->is_dead && check_proj_hit(gen, p, z, d))
				break ;
			p = p->next;
		}
		z = next_z;
	}
}

void	update_zombies_position(t_gen *gen)
{
	t_zombie	*z;
	t_draw_data	d;
	size_t		now;

	z = gen->zombies;
	if (!z)
		return ;
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
