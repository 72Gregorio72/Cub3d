/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_zombie_stats_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:32 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/01 15:54:54 by vcastald         ###   ########.fr       */
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
