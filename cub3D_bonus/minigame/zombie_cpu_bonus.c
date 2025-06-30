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

#include "cub3d_bonus.h"

void	draw_zombie_column(t_gen *gen, int screen_x,
		int draw_start, int draw_end)
{
	int		y;
	int		x_offset;
	int		width;
	int		x;

	width = 50;
	x_offset = -width / 2;
	while (x_offset <= width / 2)
	{
		x = screen_x + x_offset;
		if (x >= 0 && x < SCREEN_X)
		{
			y = draw_start;
			while (y < draw_end)
			{
				put_pixel(&gen->img, x, y, 0x00FF00);
				y++;
			}
		}
		x_offset++;
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	damage_player(t_zombie *z, t_gen *gen)
{
	t_draw_data	d;

	d.dx = gen->player.x - z->x;
	d.dy = gen->player.y - z->y;
	d.dist = sqrt(d.dx * d.dx + d.dy * d.dy);
	if (d.dist <= 0.5 && !z->attacked)
	{
		z->attacked = 1;
		z->last_attack_time = get_current_time();
		gen->health -= z->attack_power;
		z->animation_frame = 0;
		z->is_attacking = 0;
	}
	else if (d.dist > 0.5)
		update_walking(z);
}

void	damage_zombie(t_zombie *z, t_gen *gen)
{
	z->health -= 10;
	if (z->health <= 0)
	{
		z->is_dead = 1;
		z->texture = gen->zombie_tex_dead[0];
		update_dead(z);
	}
	else
	{
		z->is_hit = 1;
		z->texture = gen->zombie_tex_hit[0];
	}
	if (z->is_dead || z->is_hit)
		return ;
	update_hit(z);
}

int	check_proj_hit(t_gen *gen, t_projectile *p, t_zombie *z, t_draw_data d)
{
	if (p->active)
	{
		d.dx = p->x - z->x;
		d.dy = p->y - z->y;
		d.dist = sqrt(d.dx * d.dx + d.dy * d.dy);
		if (d.dist < 0.2)
		{
			damage_zombie(z, gen);
			p->active = 0;
			return (1);
		}
	}
	return (0);
}

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
