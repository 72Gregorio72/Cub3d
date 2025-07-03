/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:52:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/03 15:16:49 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <dirent.h>

#define MAPS_PER_ROW 3
#define MAP_BOX_W 250
#define MAP_BOX_H 50
#define START_X 100
#define START_Y 150

static char	**get_map_files(int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	dir = opendir("maps");
	if (!dir)
		return (NULL);
	files = malloc(sizeof(char *) * 100);
	if (!files)
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == 8
			&& ft_strnstr(entry->d_name, ".cub", ft_strlen(entry->d_name)))
			files[i++] = ft_strjoin("maps/", entry->d_name);
		entry = readdir(dir);
	}
	files[i] = NULL;
	*count = i;
	closedir(dir);
	return (files);
}

void	load_map1(char *path, t_gen *gen)
{
	int		fd;
	int		y;
	int		i;

	i = 0;
	y = 0;
	gen->map.map_matrix = malloc(sizeof(char *) * gen->map.height);
	if (!gen->map.map_matrix)
		return ;
	while (i < gen->map.height)
	{
		gen->map.map_matrix[i] = ft_calloc(gen->map.width + 1, sizeof(char));
		if (!gen->map.map_matrix[i])
			return ;
		i++;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	read_file(fd, i, gen, y);
	close(fd);
}

void	free_gen_map_util(t_gen *gen)
{
	gen->map.floor_color = NULL;
	gen->map.ceil_color = NULL;
	if (gen->map.n_tex)
		free(gen->map.n_tex);
	if (gen->map.s_tex)
		free(gen->map.s_tex);
	if (gen->map.w_tex)
		free(gen->map.w_tex);
	if (gen->map.e_tex)
		free(gen->map.e_tex);
}

void	free_gen_map(t_gen *gen)
{
	int	i;

	if (gen->map.map_matrix)
	{
		i = -1;
		while (++i < gen->map.height)
			free(gen->map.map_matrix[i]);
		free(gen->map.map_matrix);
		gen->map.map_matrix = NULL;
	}
	if (gen->map.floor_color)
		free(gen->map.floor_color);
	if (gen->map.ceil_color)
		free(gen->map.ceil_color);
	free_gen_map_util(gen);
	if (gen->map.c_tex)
		free(gen->map.c_tex);
	if (gen->map.f_tex)
		free(gen->map.f_tex);
}

int	get_map(char *path, t_gen *gen)
{
	free_gen_map(gen);
	if (gen->map.floor_color)
		free(gen->map.floor_color);
	if (gen->map.ceil_color)
		free(gen->map.ceil_color);
	if (gen->map.width > 0 || gen->map.height > 0)
	{
		gen->map.width = 0;
		gen->map.height = 0;
	}
	gen->map.floor_color = ft_calloc(3, sizeof(int));
	gen->map.ceil_color = ft_calloc(3, sizeof(int));
	if (!get_texture_paths(path, gen))
		return (0);
	get_map_dimensions(path, &gen->map);
	load_map1(path, gen);
	set_player_position(gen);
	if (!parsing_map(gen))
	{
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 50, 50,
			0xFF0000, "Error parsing map");
		return (0);
	}
	return (1);
}

void	start_game_from_map(t_gen *gen, const char *filepath)
{
	if (!get_map((char *)filepath, gen))
	{
		ft_printf("Failed to load map: %s\n", filepath);
		return ;
	}
	free(gen->map_file_path);
	gen->map_file_path = ft_strdup(filepath);
	draw_menu(gen);
}

void	if_checks(int i, int j, int radius, int *cx, int *cy)
{
	if (j < radius)
		*cx = radius;
	else if (j >= PREVIEW_WIDTH - radius)
		*cx = PREVIEW_WIDTH - radius - 1;
	else
		*cx = j;
	if (i < radius)
		*cy = radius;
	else if (i >= PREVIEW_HEIGHT - radius)
		*cy = PREVIEW_HEIGHT - radius - 1;
	else
		*cy = i;
}

void	draw_square(t_gen *gen, t_menu_data *data)
{
	data->dx = data->j - data->cx;
	data->dy = data->i - data->cy;
	if (data->dx * data->dx + data->dy * data->dy
		<= data->radius * data->radius)
	{
		if (data->i < PREVIEW_HEIGHT / 5)
			put_pixel(&gen->img, data->x + data->j,
				data->y + data->i, data->text_area_color);
		else
			put_pixel(&gen->img, data->x + data->j,
				data->y + data->i, data->color);
	}
}

void	draw_width(t_gen *gen, int x, int y, int i)
{
	t_menu_data	data;

	data.text_area_color = 0xFFFFFF;
	data.radius = 12;
	data.color = 0x383838;
	data.j = 0;
	data.i = i;
	data.x = x;
	data.y = y;
	while (data.j < PREVIEW_WIDTH)
	{
		if_checks(data.i, data.j, data.radius, &data.cx, &data.cy);
		draw_square(gen, &data);
		data.j++;
	}
}

void	draw_rounded_background(t_gen *gen, int x, int y)
{
	int	text_area_color;
	int	i;
	int	j;

	i = 0;
	text_area_color = 0xFFFFFF;
	while (i < PREVIEW_HEIGHT)
	{
		draw_width(gen, x, y, i);
		i++;
	}
}

void	draw_map_preview(t_gen *gen, int preview_origin_x, int preview_origin_y)
{
	int map_w = gen->map.width;
	int map_h = gen->map.height;
	int preview_cx = preview_origin_x + PREVIEW_WIDTH / 2;
	int preview_cy = preview_origin_y + PREVIEW_HEIGHT / 2;
	int max_dim = map_w + map_h;
	int cube_size = PREVIEW_WIDTH / max_dim;
	int center_offset_x = (map_w - map_h) * cube_size / 2;
	int center_offset_y = (map_w + map_h) * cube_size / 4;
	int base_x = preview_cx - center_offset_x;
	int base_y = preview_cy - center_offset_y;
	draw_rounded_background(gen, preview_origin_x, preview_origin_y);
	for (int i = 0; i < map_h; i++)
	{
		for (int j = 0; j < map_w; j++)
		{
			if (gen->map.map_matrix[i][j] == '1')
			{
				int iso_x = base_x + (j - i) * cube_size;
				int iso_y = base_y + (j + i) * cube_size / 2;

				for (int y = 0; y < cube_size; y++)
				{
					for (int x = 0; x < cube_size; x++)
					{
						int color = 0x000000;
						if (y == 0 || y == cube_size - 1 || x == 0 || x == cube_size - 1)
							color = 0xAAAAAA;
						put_pixel(&gen->img, iso_x + x, iso_y + y, color);
					}
				}
				for (int y = 0; y < 5; y++)
				{
					for (int x = 0; x < cube_size; x++)
						put_pixel(&gen->img, iso_x + x, iso_y - y, 0xEEEEEE);
				}
			}
		}
	}
}

void	start_game(t_gen *gen)
{
	gen->in_menu = 0;
	reset_player(gen);
}

void	open_map_selection(t_gen *gen)
{
	gen->map_selection = 1;
	clear_image(&gen->img);
	draw_map_selector(gen);
}

void	back_home_menu(t_gen *gen)
{
	gen->map_selection = 0;
	clear_image(&gen->img);
	draw_menu(gen);
}

void	exit_game(t_gen *gen)
{
	close_window(gen);
}

void	set_button(t_map_button *button, int x0, int y0, int x1, int y1, char *text, void (*action)(t_gen *))
{
	button->x0 = x0;
	button->y0 = y0;
	button->x1 = x1;
	button->y1 = y1;
	button->text = text;
	button->action = action;
	button->filepath = NULL;
}

void	draw_texture(t_img *img, t_tex *tex, int x0, int y0)
{
	for (int y = 0; y < tex->height; y++)
	{
		for (int x = 0; x < tex->width; x++)
		{
			char *pixel = tex->data + (y * tex->line_length + x * (tex->bpp / 8));
			unsigned int color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(img, x0 + x, y0 + y, color);
		}
	}
}

void	draw_button_debug_outline(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	for (int x = x0; x <= x1; x++)
	{
		put_pixel(img, x, y0, color);
		put_pixel(img, x, y1, color);
	}
	for (int y = y0; y <= y1; y++)
	{
		put_pixel(img, x0, y, color);
		put_pixel(img, x1, y, color);
	}
}

void	draw_button_with_action(t_gen *gen, t_map_button *button)
{
	t_tex *tex = NULL;

	if (button->action == start_game)
		tex = &gen->btn_start_game;
	else if (button->action == open_map_selection)
		tex = &gen->btn_map_selection;
	else if (button->action == exit_game)
		tex = &gen->btn_exit_game;
	else if (button->action == open_options_menu)
		tex = &gen->btn_options;
	else if (button->action == back_home_menu)
		tex = &gen->btn_back_home;
	if (tex && tex->img_ptr)
	{
		int offset_x = (button->x1 - button->x0 - tex->width) / 2;
		int offset_y = (button->y1 - button->y0 - tex->height) / 2;
		draw_texture(&gen->img, tex, button->x0 + offset_x, button->y0 + offset_y);
	}
}


void	draw_map_selector(t_gen *gen)
{
	int		i;
	int		count;
	char	**map_files;
	int		base_x[] = {100, 750, 1400};
	int		col, row;
	int		x, y;
	int		offset_y = gen->scroll_offset_y;

	clear_image(&gen->img);
	map_files = get_map_files(&count);
	if (!map_files || count == 0)
	{
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 50, 50,
			0xFF0000, "No map files found in /maps");
		return ;
	}
	gen->map_button_count = 0;
	i = 0;
	while (i < count && i < MAX_MAPS)
	{
		col = i % 3;
		row = i / 3;

		x = base_x[col];
		y = 150 + row * (PREVIEW_HEIGHT + PREVIEW_MARGIN_Y) + offset_y;
		if (get_map(map_files[i], gen))
			draw_map_preview(gen, x, y);
		free(gen->map_file_path);
		gen->map_file_path = ft_strdup(map_files[i]);
		gen->map_buttons[gen->map_button_count++] = (t_map_button){
			.x0 = x,
			.y0 = y,
			.x1 = x + PREVIEW_WIDTH,
			.y1 = y + PREVIEW_HEIGHT,
			.text = map_files[i] + 5,
			.action = NULL,
			.filepath = ft_strdup(map_files[i])
		};
		i++;
	}
	int padding = 30;
	int	button_w = 300;
	int	button_h = 130;
	t_map_button	button;
	set_button(&button,
		SCREEN_X - button_w - padding,
		padding,
		SCREEN_X - padding,
		padding + button_h,
		"", back_home_menu);
	draw_button_with_action(gen, &button);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	gen->map_buttons[3] = button;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2 - 80, 100,
		0xFFFFFF, "Select a map:");
	for (i = 0; i < gen->map_button_count; i++)
	{
		int text_x = gen->map_buttons[i].x0 + 100 - ft_strlen(gen->map_buttons[i].text) * 4;
		int text_y = gen->map_buttons[i].y0 + 20;
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, text_x, text_y, 0x000000, gen->map_buttons[i].text);
		free(map_files[i]);
	}
	free(map_files);
}

void draw_map_preview_scaled(t_gen *gen, int base_x, int base_y, int width, int height, int cube_size)
{
	int i, j;
	int top_offset = cube_size / 2;

	for (i = 0; i < height && i < gen->map.height; i++)
	{
		for (j = 0; j < width && j < gen->map.width; j++)
		{
			if (gen->map.map_matrix[i][j] == '1')
			{
				int iso_x = base_x + (j - i) * cube_size;
				int iso_y = base_y + (j + i) * cube_size / 2;

				for (int y = 0; y < cube_size; y++)
				{
					for (int x = 0; x < cube_size; x++)
					{
						int color = (x == 0 || y == 0 || x == cube_size - 1 || y == cube_size - 1) ? 0x000000 : 0xCCCCCC;
						put_pixel(&gen->img, iso_x + x, iso_y + y, color);
					}
				}
				for (int y = 0; y < top_offset; y++)
				{
					for (int x = 0; x < cube_size; x++)
					{
						int color = (x == 0 || y == 0 || x == cube_size - 1 || y == top_offset - 1) ? 0x000000 : 0xEEEEEE;
						put_pixel(&gen->img, iso_x + x, iso_y - y, color);
					}
				}
			}
			if (gen->map.map_matrix[i][j] == 'N'
				|| gen->map.map_matrix[i][j] == 'S'
				|| gen->map.map_matrix[i][j] == 'E'
				|| gen->map.map_matrix[i][j] == 'W')
			{
				int iso_x = base_x + (j - i) * cube_size;
				int iso_y = base_y + (j + i) * cube_size / 2;
				for (int y = 0; y < cube_size; y++)
					for (int x = 0; x < cube_size; x++)
						put_pixel(&gen->img, iso_x + x, iso_y + y, 0xff0000);
			}
		}
	}
}

void	draw_slider(t_gen *gen)
{
	int slider_x = 100 + (int)(gen->player_options.mouse_sensitivity * 200.0);
	for (int x = 100; x <= 300; x++)
		put_pixel(&gen->img, x, 220, 0xAAAAAA);
	for (int dx = -5; dx <= 5; dx++)
		for (int dy = -5; dy <= 5; dy++)
			put_pixel(&gen->img, slider_x + dx, 220 + dy, 0xFF0000);
	gen->dragging_slider_button.x1 = slider_x - 5;
	gen->dragging_slider_button.y1 = 215;
	gen->dragging_slider_button.x2 = slider_x + 5;
	gen->dragging_slider_button.y2 = 225;
	gen->player_options.mouse_sensitivity = (slider_x - 100) / 200.0;
}

int	update_buttons(t_gen *gen, int x, int y)
{
	int				i;
	t_key_button	key_btn;

	i = 0;
	while (i < 4)
	{
		key_btn = gen->key_buttons[i];
		if (x >= key_btn.x1 && x <= key_btn.x2
			&& y >= key_btn.y1 && y <= key_btn.y2)
		{
			gen->selected_key_index = i;
			gen->waiting_key_for = i + 1;
			open_options_menu(gen);
			return (0);
		}
		i++;
	}
	return (1);
}

void	open_options_menu(t_gen *gen)
{
	clear_image(&gen->img);
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2 - 100, 80, 0xFFFFFF, "OPTIONS");
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, 100, 200, 0xFFFFFF, "Mouse Sensitivity:");
	draw_slider(gen);
	const char *keys[] = {"UP", "DOWN", "LEFT", "RIGHT"};
	int *bindings[] = {
		&gen->player_options.key_up,
		&gen->player_options.key_down,
		&gen->player_options.key_left,
		&gen->player_options.key_right
	};
	for (int i = 0; i < 4; i++)
	{
		int y = 300 + i * 50;
		int bx1 = 300, by1 = y - 10;
		int bx2 = 360, by2 = y + 20;
		char *key_name = mlx_get_key_name(*bindings[i]);
		char *tmp = ft_strjoin(keys[i], ": ");
		char *buf = ft_strjoin(tmp, key_name);
		free(tmp);
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 100, y, 0xFFFFFF, buf);
		int color = 0xAAAAAA;
		if (gen->selected_key_index == i)
		{
			color = 0xFFFFFF;
			mlx_string_put(gen->mlx_ptr, gen->win_ptr, 400, y + 10, 0xFFFFFF, "Press a new key");
		}
		for (int x = bx1; x <= bx2; x++)
			for (int y2 = by1; y2 <= by2; y2++)
				put_pixel(&gen->img, x, y2, color);
		gen->key_buttons[i].x1 = bx1;
		gen->key_buttons[i].y1 = by1;
		gen->key_buttons[i].x2 = bx2;
		gen->key_buttons[i].y2 = by2;
		gen->key_buttons[i].key = bindings[i];
		gen->key_buttons[i].label = keys[i];
	}
	set_button(&gen->map_buttons[0],
		SCREEN_X - 250, SCREEN_Y - 100,
		SCREEN_X - 50, SCREEN_Y - 50,
		"BACK", draw_menu);
	gen->map_button_count = 1;
	draw_button_with_action(gen, &gen->map_buttons[0]);
	gen->selected_key_index = -1;
}

void	draw_menu(t_gen *gen)
{
	int	map_area_x = 500;
	int	map_area_y = 300;
	int	button_w = 400;
	int	button_h = 180;
	int	button_spacing = 40;
	int	right_column_x = SCREEN_X - button_w - 100;
	int	button_start_y = 200;
	int	i = 0;

	gen->in_menu = 1;
	clear_image(&gen->img);
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	char *title = "CUB3D";
	int title_x = (SCREEN_X - ft_strlen(title) * 20) / 2;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, title_x, 80, 0xFFFFFF, title);
	if (gen->map.map_matrix && gen->map.width > 0 && gen->map.height > 0)
	{
		draw_map_preview_scaled(gen, map_area_x, map_area_y,
			gen->map.width, gen->map.height, 15);
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			map_area_x, map_area_y - 30, 0xFFFFFF, "MAPPA");
	}
	gen->map_button_count = 0;
	int extra_spacing = 60;
	set_button(&gen->map_buttons[gen->map_button_count++],
		right_column_x, button_start_y,
		right_column_x + button_w, button_start_y + button_h,
		"START", start_game);
	set_button(&gen->map_buttons[gen->map_button_count++],
		right_column_x, button_start_y + button_h + button_spacing + extra_spacing,
		right_column_x + button_w, button_start_y + 2 * button_h + button_spacing + extra_spacing,
		"SELECT", open_map_selection);
	set_button(&gen->map_buttons[gen->map_button_count++],
		right_column_x, button_start_y + 2 * (button_h + button_spacing + extra_spacing),
		right_column_x + button_w, button_start_y + 3 * button_h + 2 * (button_spacing + extra_spacing),
		"QUIT", exit_game);
	set_button(&gen->map_buttons[gen->map_button_count++],
		right_column_x, button_start_y + 3 * (button_h + button_spacing + extra_spacing),
		right_column_x + button_w, button_start_y + 4 * button_h + 3 * (button_spacing + extra_spacing),
		"OPTIONS", open_options_menu);
	while (i < gen->map_button_count)
		draw_button_with_action(gen, &gen->map_buttons[i++]);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
}
