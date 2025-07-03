/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:52:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/07/03 16:50:30 by gpicchio         ###   ########.fr       */
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

	i = 0;
	text_area_color = 0xFFFFFF;
	while (i < PREVIEW_HEIGHT)
	{
		draw_width(gen, x, y, i);
		i++;
	}
}

void	set_preview(t_map_preview *preview,
	t_gen *gen, int preview_origin_x, int preview_origin_y)
{
	preview->map_w = gen->map.width;
	preview->map_h = gen->map.height;
	preview->preview_cx = preview_origin_x + PREVIEW_WIDTH / 2;
	preview->preview_cy = preview_origin_y + PREVIEW_HEIGHT / 2;
	preview->max_dim = preview->map_w + preview->map_h;
	preview->cube_size = PREVIEW_WIDTH / preview->max_dim;
	preview->center_offset_x = (preview->map_w - preview->map_h)
		* preview->cube_size / 2;
	preview->center_offset_y = (preview->map_w + preview->map_h)
		* preview->cube_size / 4;
	preview->base_x = preview->preview_cx - preview->center_offset_x;
	preview->base_y = preview->preview_cy - preview->center_offset_y;
	draw_rounded_background(gen, preview_origin_x, preview_origin_y);
}

void	draw_wall_cube(t_gen *gen, t_map_preview *preview)
{
	while (preview->y < preview->cube_size)
	{
		preview->x = 0;
		while (preview->x < preview->cube_size)
		{
			preview->color = 0x000000;
			if (preview->y == 0 || preview->y == preview->cube_size - 1
				|| preview->x == 0 || preview->x == preview->cube_size - 1)
				preview->color = 0xAAAAAA;
			put_pixel(&gen->img, preview->iso_x
				+ preview->x, preview->iso_y + preview->y, preview->color);
			preview->x++;
		}
		preview->y++;
	}
}

void	draw_wall_preview(t_gen *gen, t_map_preview *preview)
{
	if (gen->map.map_matrix[preview->i][preview->j] == '1')
	{
		preview->iso_x = preview->base_x
			+ (preview->j - preview->i) * preview->cube_size;
		preview->iso_y = preview->base_y
			+ (preview->j + preview->i) * preview->cube_size / 2;
		preview->y = 0;
		draw_wall_cube(gen, preview);
		preview->y = 0;
		while (preview->y < 5)
		{
			preview->x = 0;
			while (preview->x < preview->cube_size)
			{
				put_pixel(&gen->img, preview->iso_x
					+ preview->x, preview->iso_y - preview->y, 0xEEEEEE);
				preview->x++;
			}
			preview->y++;
		}
	}
}

void	draw_map_preview(t_gen *gen, int preview_origin_x, int preview_origin_y)
{
	t_map_preview	preview;

	set_preview(&preview, gen, preview_origin_x, preview_origin_y);
	preview.i = 0;
	while (preview.i < preview.map_h)
	{
		preview.j = 0;
		while (preview.j < preview.map_w)
		{
			draw_wall_preview(gen, &preview);
			preview.j++;
		}
		preview.i++;
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
	int				y;
	int				x;
	char			*pixel;
	unsigned int	color;

	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			pixel = tex->data + (y * tex->line_length + x * (tex->bpp / 8));
			color = *(unsigned int *)pixel;
			if ((color & 0x00FFFFFF) != 0x000000)
				put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	draw_button_debug_outline(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int		x;
	int		y;

	x = x0;
	while (x <= x1)
	{
		put_pixel(img, x, y0, color);
		put_pixel(img, x, y1, color);
		x++;
	}
	y = y0;
	while (y <= y1)
	{
		put_pixel(img, x0, y, color);
		put_pixel(img, x1, y, color);
		y++;
	}
}

void	draw_button_with_action(t_gen *gen, t_map_button *button)
{
	t_tex	*tex;
	int		offset_x;
	int		offset_y;

	tex = NULL;
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
	offset_x = (button->x1 - button->x0 - tex->width) / 2;
	offset_y = (button->y1 - button->y0 - tex->height) / 2;
	if (tex && tex->img_ptr)
		draw_texture(&gen->img, tex, button->x0
			+ offset_x, button->y0 + offset_y);
}

void	set_map_preview(t_gen *gen, t_map_selector *map)
{
	map->base_x[0] = 100;
	map->base_x[1] = 750;
	map->base_x[2] = 1400;
	map->offset_y = gen->scroll_offset_y;
	map->padding = 30;
	map->button_w = 300;
	map->button_h = 130;

	clear_image(&gen->img);
	map->map_files = get_map_files(&map->count);
	if (!map->map_files || map->count == 0)
	{
		mlx_string_put(gen->mlx_ptr, gen->win_ptr, 50, 50,
			0xFF0000, "No map files found in /maps");
		return ;
	}
	gen->map_button_count = 0;
	map->i = 0;
}

void	draw_map_ui(t_map_selector *map, t_gen *gen)
{
	while (map->i < map->count && map->i < MAX_MAPS)
	{
		map->col = map->i % 3;
		map->row = map->i / 3;
		map->x = map->base_x[map->col];
		map->y = 150 + map->row
			* (PREVIEW_HEIGHT + PREVIEW_MARGIN_Y) + map->offset_y;
		if (get_map(map->map_files[map->i], gen))
			draw_map_preview(gen, map->x, map->y);
		free(gen->map_file_path);
		gen->map_file_path = ft_strdup(map->map_files[map->i]);
		gen->map_buttons[gen->map_button_count++] = (t_map_button){
			.x0 = map->x,
			.y0 = map->y,
			.x1 = map->x + PREVIEW_WIDTH,
			.y1 = map->y + PREVIEW_HEIGHT,
			.text = map->map_files[map->i] + 5,
			.action = NULL,
			.filepath = ft_strdup(map->map_files[map->i])
		};
		map->i++;
	}
}

void	write_filename(t_map_selector *map, t_gen *gen)
{
	map->j = 0;
	while (map->j < gen->map_button_count)
	{
		map->text_x = gen->map_buttons[map->j].x0
			+ 100 - ft_strlen(gen->map_buttons[map->j].text) * 4;
		map->text_y = gen->map_buttons[map->j].y0 + 20;
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			map->text_x, map->text_y, 0x000000, gen->map_buttons[map->j].text);
		free(map->map_files[map->j]);
		map->j++;
	}
}

void	draw_map_selector(t_gen *gen)
{
	t_map_selector	map;

	set_map_preview(gen, &map);
	draw_map_ui(&map, gen);
	set_button(&map.button,
		SCREEN_X - map.button_w - map.padding,
		map.padding,
		SCREEN_X - map.padding,
		map.padding + map.button_h,
		"", back_home_menu);
	draw_button_with_action(gen, &map.button);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	gen->map_buttons[3] = map.button;
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, SCREEN_X / 2 - 80, 100,
		0xFFFFFF, "Select a map:");
	write_filename(&map, gen);
	free(map.map_files);
}

// void draw_map_preview_scaled(t_gen *gen, int base_x, int base_y, int width, int height, int cube_size)
// {
// 	int i, j, x, y;
// 	int iso_x, iso_y;
// 	int color;
// 	int top_offset = cube_size / 2;

// 	i = 0;
// 	while (i < height && i < gen->map.height)
// 	{
// 		j = 0;
// 		while (j < width && j < gen->map.width)
// 		{
// 			if (gen->map.map_matrix[i][j] == '1')
// 			{
// 				iso_x = base_x + (j - i) * cube_size;
// 				iso_y = base_y + (j + i) * cube_size / 2;

// 				y = 0;
// 				while (y < cube_size)
// 				{
// 					x = 0;
// 					while (x < cube_size)
// 					{
// 						color = (x == 0 || y == 0 || x == cube_size - 1 || y == cube_size - 1) ? 0x000000 : 0xCCCCCC;
// 						put_pixel(&gen->img, iso_x + x, iso_y + y, color);
// 						x++;
// 					}
// 					y++;
// 				}
// 				y = 0;
// 				while (y < top_offset)
// 				{
// 					x = 0;
// 					while (x < cube_size)
// 					{
// 						color = (x == 0 || y == 0 || x == cube_size - 1 || y == top_offset - 1) ? 0x000000 : 0xEEEEEE;
// 						put_pixel(&gen->img, iso_x + x, iso_y - y, color);
// 						x++;
// 					}
// 					y++;
// 				}
// 			}
// 			if (gen->map.map_matrix[i][j] == 'N'
// 				|| gen->map.map_matrix[i][j] == 'S'
// 				|| gen->map.map_matrix[i][j] == 'E'
// 				|| gen->map.map_matrix[i][j] == 'W')
// 			{
// 				iso_x = base_x + (j - i) * cube_size;
// 				iso_y = base_y + (j + i) * cube_size / 2;
// 				y = 0;
// 				while (y < cube_size)
// 				{
// 					x = 0;
// 					while (x < cube_size)
// 					{
// 						put_pixel(&gen->img, iso_x + x, iso_y + y, 0xff0000);
// 						x++;
// 					}
// 					y++;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	set_slider(t_gen *gen, int slider_x)
{
	gen->dragging_slider_button.x1 = slider_x - 5;
	gen->dragging_slider_button.y1 = 215;
	gen->dragging_slider_button.x2 = slider_x + 5;
	gen->dragging_slider_button.y2 = 225;
	gen->player_options.mouse_sensitivity = (slider_x - 100) / 200.0;
}

void	draw_slider(t_gen *gen)
{
	int	slider_x;
	int	x;
	int	dx;
	int	dy;

	slider_x = 100 + (int)(gen->player_options.mouse_sensitivity * 200.0);
	x = 100;
	while (x <= 300)
	{
		put_pixel(&gen->img, x, 220, 0xAAAAAA);
		x++;
	}
	dx = -5;
	while (dx <= 5)
	{
		dy = -5;
		while (dy <= 5)
		{
			put_pixel(&gen->img, slider_x + dx, 220 + dy, 0xFF0000);
			dy++;
		}
		dx++;
	}
	set_slider(gen, slider_x);
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

void	set_options(t_gen *gen, t_option_data *data)
{
	data->y = 300 + data->i * 50;
	data->bx1 = 300;
	data->by1 = data->y - 10;
	data->bx2 = 360;
	data->by2 = data->y + 20;
	data->key_name = mlx_get_key_name(*(data->bindings[data->i]));
	data->tmp = ft_strjoin(data->keys[data->i], ": ");
	data->buf = ft_strjoin(data->tmp, data->key_name);
	free(data->tmp);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, 100,
		data->y, 0xFFFFFF, data->buf);
	free(data->buf);
	data->color = 0xAAAAAA;
	if (gen->selected_key_index == data->i)
	{
		data->color = 0xFFFFFF;
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			400, data->y + 10, 0xFFFFFF, "Press a new key");
	}
}

void	set_option_data(t_option_data *data, t_gen *gen)
{
	data->keys[0] = ft_strdup("UP");
	data->keys[1] = ft_strdup("DOWN");
	data->keys[2] = ft_strdup("LEFT");
	data->keys[3] = ft_strdup("RIGHT");
	data->bindings[0] = &gen->player_options.key_up;
	data->bindings[1] = &gen->player_options.key_down;
	data->bindings[2] = &gen->player_options.key_left;
	data->bindings[3] = &gen->player_options.key_right;
	clear_image(&gen->img);
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr,
		SCREEN_X / 2 - 100, 80, 0xFFFFFF, "OPTIONS");
	mlx_string_put(gen->mlx_ptr, gen->win_ptr,
		100, 200, 0xFFFFFF, "Mouse Sensitivity:");
	draw_slider(gen);
}

void	draw_option(t_option_data *data, t_gen *gen)
{
	data->x = data->bx1;
	while (data->x <= data->bx2)
	{
		data->y2 = data->by1;
		while (data->y2 <= data->by2)
		{
			put_pixel(&gen->img, data->x, data->y2, data->color);
			data->y2++;
		}
		data->x++;
	}
	gen->key_buttons[data->i].x1 = data->bx1;
	gen->key_buttons[data->i].y1 = data->by1;
	gen->key_buttons[data->i].x2 = data->bx2;
	gen->key_buttons[data->i].y2 = data->by2;
	gen->key_buttons[data->i].key = data->bindings[data->i];
	gen->key_buttons[data->i].label = data->keys[data->i];
}

void	open_options_menu(t_gen *gen)
{
	t_option_data	data;

	set_option_data(&data, gen);
	data.i = 0;
	while (data.i < 4)
	{
		set_options(gen, &data);
		draw_option(&data, gen);
		data.i++;
	}
	set_button(&gen->map_buttons[0],
		SCREEN_X - 250, SCREEN_Y - 100,
		SCREEN_X - 50, SCREEN_Y - 50,
		"BACK", draw_menu);
	gen->map_button_count = 1;
	draw_button_with_action(gen, &gen->map_buttons[0]);
	gen->selected_key_index = -1;
}

void	set_buttons(t_gen *gen)
{
	int	i;

	i = 0;
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 200,
		SCREEN_X - 400 - 100 + 400, 200 + 180,
		"START", start_game);
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 200 + 180 + 40 + 60,
		SCREEN_X - 400 - 100 + 400, 200 + 2 * 180 + 40 + 60,
		"SELECT", open_map_selection);
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 200 + 2 * (180 + 40 + 60),
		SCREEN_X - 400 - 100 + 400, 200 + 3 * 180 + 2 * (40 + 60),
		"QUIT", exit_game);
	set_button(&gen->map_buttons[gen->map_button_count++],
		SCREEN_X - 400 - 100, 200 + 3 * (180 + 40 + 60),
		SCREEN_X - 400 - 100 + 400, 200 + 4 * 180 + 3 * (40 + 60),
		"OPTIONS", open_options_menu);
	while (i < gen->map_button_count)
		draw_button_with_action(gen, &gen->map_buttons[i++]);
}

void	draw_menu(t_gen *gen)
{
	int	title_x;

	title_x = (SCREEN_X - ft_strlen("CUB3D") * 20) / 2;
	gen->map_selection = 0;
	gen->in_menu = 1;
	clear_image(&gen->img);
	mlx_clear_window(gen->mlx_ptr, gen->win_ptr);
	mlx_string_put(gen->mlx_ptr, gen->win_ptr, title_x, 80, 0xFFFFFF, "CUB3D");
	if (gen->map.map_matrix && gen->map.width > 0 && gen->map.height > 0)
	{
		draw_map_preview(gen, 100, 150);
		mlx_string_put(gen->mlx_ptr, gen->win_ptr,
			500, 300 - 30, 0xFFFFFF, "MAPPA");
	}
	gen->map_button_count = 0;
	set_buttons(gen);
	mlx_put_image_to_window(gen->mlx_ptr, gen->win_ptr, gen->img.img_ptr, 0, 0);
}
