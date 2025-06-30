/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:48 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/30 11:39:02 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_main(t_gen *gen)
{
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
}

t_tex *get_texture(char *path, t_gen *gen)
{
	t_tex *tex = malloc(sizeof(t_tex));
	if (!tex)
		return (NULL);
	//load_texture(gen->mlx_ptr, path, tex);
	tex->img_ptr = mlx_xpm_file_to_image(gen->mlx_ptr, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf(RED "Error loading texture: %s\n" RESET, path);
		free(tex);
		return (NULL);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_length, &tex->endian);
	//ft_printf("texture: %s\n", tex->data);
	return (tex);
}

void	load_animation(t_gen *gen, const char *base_path, t_tex **tex_array, int count)
{
	for (int i = 0; i < count; i++)
	{
		char *num = ft_itoa(i);
		char *ext = ft_strjoin(base_path, num);
		char *path = ft_strjoin(ext, ".xpm");
		free(num);
		free(ext);
		if (!path)
			continue ;
		tex_array[i] = get_texture(path, gen);
		if (!tex_array[i])
		{
			fprintf(stderr, RED "Failed to load texture: %s\n" RESET, path);
			free(path);
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
	load_animation(gen, "zombie_anim/walking_xpm/Zwalking", gen->zombie_tex_walking, 26);
	load_animation(gen, "zombie_anim/attacking_xpm/Zattacking", gen->zombie_tex_attacking, 17);
	// load_animation(gen, "textures/zombie/dead/Zdying", gen->zombie_tex_dead, 21);
	// load_animation(gen, "textures/zombie/hit/Zhitted", gen->zombie_tex_hit, 13);
}

