/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:48 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/03 10:32:31 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_button_images(t_gen *gen)
{
	gen->btn_start_game = *get_texture("textures/start_btn.xpm", gen);
	gen->btn_map_selection = *get_texture("textures/select_map.xpm", gen);
	gen->btn_exit_game = *get_texture("textures/quit.xpm", gen);
}

void	init_main(t_gen *gen)
{
	srand(time(NULL));
	gen->num_zombies = 0;
	gen->projectiles = NULL;
	gen->mouse_initialized = 0;
	gen->ignore_next_mouse = 0;
	gen->last_mouse_x = SCREEN_X / 2;
	gen->last_mouse_y = SCREEN_Y / 2;
	gen->zombies = NULL;
	gen->max_health = 100;
	gen->health = gen->max_health;
	gen->ammo = 10;
	gen->mouse_vertical_offset = 0;
	gen->in_menu = 1;
	gen->map_button_count = 0;
	gen->counter_spawn = 0;
}

t_tex	*get_texture(char *path, t_gen *gen)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	if (!tex)
		return (NULL);
	tex->img_ptr = mlx_xpm_file_to_image(gen->mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf(RED "Error loading texture: %s\n" RESET, path);
		free(tex);
		return (NULL);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_length, &tex->endian);
	return (tex);
}

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
	load_texture(gen->mlx_ptr, "textures/door/door.xpm",
		&gen->door.door_closed);
	load_texture(gen->mlx_ptr, "textures/door/door1.xpm",
		&gen->door.door_half_open);
	load_texture(gen->mlx_ptr, "textures/door/door2.xpm", &gen->door.door_open);
	load_animation(gen, "zombie_anim/walking_xpm/Zwalking",
		gen->zombie_tex_walking, 26);
	load_animation(gen, "zombie_anim/attacking_xpm/Zattacking",
		gen->zombie_tex_attacking, 17);
	load_animation(gen, "zombie_anim/dying_xpm/Zdying",
			gen->zombie_tex_dead, 21);
	load_animation(gen, "zombie_anim/hitted_xpm/Zhitted",
			gen->zombie_tex_hit, 13);
}

void	reset_player(t_gen *gen)
{
	get_map(gen->map_file_path, gen);
}
