/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_zombies_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:45:12 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 15:45:40 by vcastald         ###   ########.fr       */
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
	if (z->is_dead && z->is_hit)
		return ;
	z->is_walking = 0;
	z->is_attacking = 1;
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
	if (z->is_dead && z->is_hit)
		return ;
	z->is_walking = 0;
	z->is_attacking = 0;
	z->is_hit = 1;
	z->animation_frame = 0;
}
