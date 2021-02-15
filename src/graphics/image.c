/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:20:30 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/15 15:20:32 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

void	clear_screen(t_window v)
{
	int x;
	int y;

	y = 0;
	while (y < g_game->heigth)
	{
		x = 0;
		while (x < g_game->width)
		{
			v.img->put_pixel(v, x, y, 0);
			x++;
		}
		y++;
	}
	v.img->show(v);
}

void	show_image(t_window v)
{
	mlx_put_image_to_window(v.mlx, v.win, v.img->img_ptr, 0, 0);
}

void	init_image(t_image *this, t_window win)
{
	if (this != NULL)
	{
		this->img_ptr = mlx_new_image(win.mlx, g_game->width, g_game->heigth);
		this->img_data = mlx_get_data_addr(this->img_ptr,
			&this->bpp, &this->size_line, &this->endian);
		this->put_pixel = &image_put_pixel;
		this->clear = &clear_screen;
		this->show = &show_image;
	}
}
