/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:31:28 by vcastald          #+#    #+#             */
/*   Updated: 2025/06/19 15:49:27 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_keypress(int keysym, t_gen *gen)
{
	if (keysym == KB_ESC)
	{
		close_window(gen);
		exit(0);
	}
	return (0);
}

int	pre_checks(int ac, char **av, t_gen *gen)
{
	char	*dot;

	if (ac != 2)
		return (printf(RED"Error: wrong number of arguments!\n"RESET), 0);
	dot = ft_strchr(av[1], '.');
	if (!dot || ft_strncmp(dot, ".cub", 4) || ft_strlen(dot) != 4)
		return (printf(RED"Error: "YELLOW"%s"RED" is not a .cub!\n"RESET, av[1]), 0);
	gen->map.fd_map = open(av[1], O_RDONLY);
	if (gen->map.fd_map == -1)
		return (printf(RED"Error: file not found!\n"RESET), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_gen	gen;

	(void)ac;
	(void)av;
 	if (!pre_checks(ac, av, &gen))
		return (0);
	read_map(av, &gen);
	printf(GREEN"Map loaded successfully!\n"RESET);
	printf("Map dimensions: %d x %d\n", gen.map.width, gen.map.height);
	gen.mlx_ptr = mlx_init();
	gen.win_ptr = mlx_new_window(gen.mlx_ptr, SCREEN_X, SCREEN_Y, "cub3D"); 
	mlx_hook(gen.win_ptr, KeyPress, KeyPressMask,
		&on_keypress, &gen);
	mlx_hook(gen.win_ptr, DestroyNotify, StructureNotifyMask,
		&close_window, &gen);
	mlx_loop(gen.mlx_ptr);
	close_window(&gen);
	return (0);
}
