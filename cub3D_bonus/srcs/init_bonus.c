/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:36:48 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/10 16:06:11 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_button_images(t_gen *gen)
{
	load_texture(gen->mlx_ptr, "textures/start_btn.xpm", &gen->btn_start_game);
	load_texture(gen->mlx_ptr, "textures/select_map.xpm",
		&gen->btn_map_selection);
	load_texture(gen->mlx_ptr, "textures/quit.xpm", &gen->btn_exit_game);
	load_texture(gen->mlx_ptr, "textures/option_btn.xpm", &gen->btn_options);
	load_texture(gen->mlx_ptr,
		"textures/red_cross_tiny.xpm", &gen->btn_back_home);
}

void	init_keys(t_gen *gen)
{
	gen->player_options.mouse_sensitivity = MOUSE_SENSITIVITY;
	gen->player_options.key_up = KB_W;
	gen->player_options.key_down = KB_S;
	gen->player_options.key_left = KB_A;
	gen->player_options.key_right = KB_D;
}

void	init_edited_map(int edited_map[100][100])
{
	int	i;
	int	j;

	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			edited_map[i][j] = 0;
			j++;
		}
		i++;
	}
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
	gen->counter_spawn = 0;
	gen->scroll_offset_y = 0;
	init_keys(gen);
	gen->in_options = 0;
	gen->waiting_key_for = 0;
	gen->selected_key_index = -1;
	gen->dragging_slider = 0;
	gen->map_selection = 0;
	gen->door.flag_door_open = 0;
	gen->is_initializing = 0;
	gen->is_drawing = 0;
	init_edited_map(gen->edited_map);
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

void	reset_player(t_gen *gen)
{
	get_map(gen->map_file_path, gen);
	gen->health = gen->max_health;
	reset_zombies(gen);
	load_zombies(gen);
	rotate_view(gen);
}
