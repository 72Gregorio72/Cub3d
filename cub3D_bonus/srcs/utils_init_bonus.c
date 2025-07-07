/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:28:43 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/07 11:44:48 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	util_load_animation(char **ext,
	char **path, const char *base_path, char *num)
{
	*ext = ft_strjoin(base_path, num);
	*path = ft_strjoin(*ext, ".xpm");
	free(num);
	free(*ext);
}

void	load_animation(t_gen *gen, const char *base_path,
	t_tex **tex_array, int count)
{
	int		i;
	char	*num;
	char	*ext;
	char	*path;

	i = -1;
	while (++i < count)
	{
		num = ft_itoa(i);
		util_load_animation(&ext, &path, base_path, num);
		if (!path)
		{
			i++;
			continue ;
		}
		tex_array[i] = get_texture(path, gen);
		if (!tex_array[i])
		{
			free(path);
			i++;
			continue ;
		}
		free(path);
	}
}

void	load_textures(t_gen *gen)
{
	gen->keys = (t_keys){0, 0, 0, 0, 0, 0};
	init_image(gen);
	load_texture(gen->mlx_ptr, gen->map.n_tex, &gen->map.north);
	load_texture(gen->mlx_ptr, gen->map.s_tex, &gen->map.south);
	load_texture(gen->mlx_ptr, gen->map.e_tex, &gen->map.east);
	load_texture(gen->mlx_ptr, gen->map.w_tex, &gen->map.west);
	load_texture(gen->mlx_ptr, "textures/cubed_title.xpm", &gen->title_tex);
	load_texture(gen->mlx_ptr, "textures/door/door.xpm",
		&gen->door.door_closed);
	load_animation(gen, "zombie_anim/walking_xpm/Zwalking",
		gen->zombie_tex_walking, 26);
	load_animation(gen, "zombie_anim/attacking_xpm/Zattacking",
		gen->zombie_tex_attacking, 17);
	load_animation(gen, "zombie_anim/dying_xpm/Zdying",
		gen->zombie_tex_dead, 21);
	load_animation(gen, "zombie_anim/hitted_xpm/Zhitted",
		gen->zombie_tex_hit, 13);
}

void	reset_zombies(t_gen *gen)
{
	t_zombie	*current;
	t_zombie	*next;

	current = gen->zombies;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	gen->zombies = NULL;
	gen->num_zombies = 0;
	gen->counter_spawn = 0;
}
