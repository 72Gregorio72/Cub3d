/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:52:09 by gpicchio          #+#    #+#             */
/*   Updated: 2025/06/30 14:58:01 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_menu(t_gen *gen)
{
	int		x;
	int		y;
	char	*menu_text;

	menu_text = "Press 'W' to start the game";
	x = (SCREEN_X - ft_strlen(menu_text) * 10) / 2;
	y = SCREEN_Y / 2;
	while (*menu_text)
	{
		put_pixel(&gen->img, x, y, 0xFFFFFF);
		x += 10;
		menu_text++;
	}
}