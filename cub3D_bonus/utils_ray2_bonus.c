/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:55:35 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/23 12:13:55 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	clear_image(t_img *img)
{
	int	y;

	y = 0;
	while (y < SCREEN_Y)
	{
		ft_bzero(img->data + y * img->line_length, img->line_length);
		y++;
	}
}

t_tex	*select_texture(t_ray *ray, t_gen *gen)
{
	if (ray->side == 0)
	{
		if (gen->player.ray_dir_x < 0)
			return (&gen->map.west);
		else
			return (&gen->map.east);
	}
	else
	{
		if (gen->player.ray_dir_y < 0)
			return (&gen->map.north);
		else
			return (&gen->map.south);
	}
}

int	pre_checks(int ac, char **av, t_gen *gen)
{
	char	*dot;

	if (ac != 2)
		return (printf(RED"Error: wrong number of arguments!\n"RESET), 0);
	dot = ft_strchr(av[1], '.');
	if (!dot || ft_strncmp(dot, ".cub", 4) || ft_strlen(dot) != 4)
		return (printf(RED"Error: "YELLOW"%s"RED" is not a .cub!\n"RESET,
				av[1]), 0);
	gen->map.fd_map = open(av[1], O_RDONLY);
	if (gen->map.fd_map == -1)
		return (printf(RED"Error: file not found!\n"RESET), 0);
	return (1);
}

void	clean_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n'
			|| path[len - 1] == '\r' || path[len - 1] == ' '))
		path[--len] = '\0';
}

void	load_texture(void *mlx, char *path, t_tex *tex)
{
	clean_path(path);
	tex->img_ptr = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf(RED"Failed to load texture: %s\n"RESET, path);
		exit(EXIT_FAILURE);
	}
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_length, &tex->endian);
}
