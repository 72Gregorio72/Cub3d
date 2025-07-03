/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie_animator_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:37:08 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/03 10:37:08 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	util_animate_zombie(t_zombie *z, t_gen *gen)
{
	if (z->is_hit)
	{
		z->animation_frame++;
		if (z->animation_frame >= 13)
		{
			printf(GREEN"Zombie hit animation finished\n"RESET);
			z->is_hit = 0;
			z->animation_frame = 0;
			z->is_walking = 1;
		}
		z->texture = gen->zombie_tex_hit[z->animation_frame];
	}
	else if (z->is_attacking)
	{
		z->animation_frame++;
		if (z->animation_frame >= 17)
			damage_player(z, gen);
		z->texture = gen->zombie_tex_attacking[z->animation_frame];
	}
}

void	animate_zombies(t_gen *gen)
{
	t_zombie	*z;

	z = gen->zombies;
	while (z)
	{
		if (z->is_dead)
		{
			z->animation_frame++;
			if (z->animation_frame >= 21)
				remove_zombie(gen, z);
			z->texture = gen->zombie_tex_dead[z->animation_frame];
		}
		else if (z->is_walking)
		{
			z->animation_frame++;
			if (z->animation_frame >= 26)
				z->animation_frame = 0;
			z->texture = gen->zombie_tex_walking[z->animation_frame];
		}
		util_animate_zombie(z, gen);
		z = z->next;
	}
}
