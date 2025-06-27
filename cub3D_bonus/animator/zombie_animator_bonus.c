/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie_animator_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:56:24 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 10:56:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_walking(t_zombie *z)
{
	z->is_walking = 1;
	z->is_attacking = 0;
	z->is_dead = 0;
	z->is_hit = 0;
	z->animation_frame = 0;
}

void	update_attacking(t_zombie *z)
{
	z->is_walking = 0;
	z->is_attacking = 1;
	z->is_dead = 0;
	z->is_hit = 0;
}

void	update_dead(t_zombie *z)
{
	z->is_walking = 0;
	z->is_attacking = 0;
	z->is_dead = 1;
	z->is_hit = 0;
	z->animation_frame = 0;
}

void	update_hit(t_zombie *z)
{
	z->is_walking = 0;
	z->is_attacking = 0;
	z->is_dead = 0;
	z->is_hit = 1;
	z->animation_frame = 0;
}

void	animate_zombies(t_gen *gen)
{
	t_zombie	*z;

	z = gen->zombies;
	while (z)
	{
		if (z->is_walking)
		{
			z->animation_frame++;
			if (z->animation_frame >= 26)
				z->animation_frame = 0;
			z->texture = gen->zombie_tex_walking[z->animation_frame];
		}
		else if (z->is_attacking)
		{
			z->animation_frame++;
			if (z->animation_frame >= 17)
				damage_player(z, gen);
			z->texture = gen->zombie_tex_attacking[z->animation_frame];
		}
		else if (z->is_dead)
		{
			z->animation_frame++;
			if (z->animation_frame >= 21)
				z->animation_frame = 0;
			z->texture = gen->zombie_tex_dead[z->animation_frame];
		}
		else if (z->is_hit)
		{
			z->animation_frame++;
			if (z->animation_frame >= 13)
				z->animation_frame = 0;
			z->texture = gen->zombie_tex_hit[z->animation_frame];
		}
		z = z->next;
	}
}
