/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:48 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/27 11:13:13 by marvin           ###   ########.fr       */
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
	tex->img_ptr = mlx_xpm_file_to_image(gen->mlx_ptr, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf(RED "Error loading texture: %s\n" RESET, path);
		free(tex);
		return (NULL);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_length, &tex->endian);
	return (tex);
}

void	load_textures(t_gen *gen)
{
	gen->keys = (t_keys){0, 0, 0, 0, 0, 0};
	init_image(gen);
	load_texture(gen->mlx_ptr, gen->map.n_tex, &gen->map.north);
	load_texture(gen->mlx_ptr, gen->map.s_tex, &gen->map.south);
	load_texture(gen->mlx_ptr, gen->map.e_tex, &gen->map.east);
	load_texture(gen->mlx_ptr, gen->map.w_tex, &gen->map.west);

	for (int i = 0; i < 17; i++)
	{
		char *base = ft_strdup("zombie_anim/attacking_xpm/Zattacking");
		char *num = ft_itoa(i);
		char *tmp = ft_strjoin(base, num);
		char *path = ft_strjoin(tmp, ".xpm");

		free(base);
		free(num);
		free(tmp);

		t_tex *tex = get_texture(path, gen);
		if (!tex)
		{
			fprintf(stderr, RED "Failed to load zombie texture frame %d\n" RESET, i);
			free(path);
			continue;
		}
		gen->zombie_tex_walking[i] = tex;
		free(path);
	}
}

