/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:53:58 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:54:00 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


extern t_game *g_game;

void	rec(int  x ,int  y, int  sizex ,int sizey, int color)
{
	int x2;
	int y2;
	int vx;

	y2 = y + sizey;
	x2 = x + sizex;
	while (y < y2)
	{
		vx = x;
		while (vx < x2)
		{
			g_game->window.img->put_pixel(g_game->window,  vx, y, color);
			vx++;
		}
		y += 1;
	}

}

void    init_image(t_image *this,t_window win)
{
	if(this != NULL)
	{
		this->img_ptr = mlx_new_image(win.mlx, g_game->width, g_game->heigth);
		this->img_data = mlx_get_data_addr(this->img_ptr, &this->bpp, &this->size_line, &this->endian);
		this->put_pixel = &image_put_pixel;
		this->clear = &clear_screen;
		this->show = &show_image;
	}
}

int rgb_to_int(int r, int g, int b)
{
	int c;
	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

int		shadow(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	float	fact;

	fact = 200 / distance;
	b = (color & 0xff) * fact;
	b = b > (color & 0xff) ? (color & 0xff) : b;
	color = color >> 8;
	g = (color & 0xff) * fact;
	g = g > (color & 0xff) ? (color & 0xff) : g;
	color = color >> 8;
	r = (color & 0xff) * fact;
	r = r > (color & 0xff) ? (color & 0xff) : r;
	return (rgb_to_int(r, g, b));
}

void	image_put_pixel(t_window v, int x, int y, int color)
{
	int i;

	if (x < 0 || y < 0 || x >= g_game->width || y >= g_game->heigth)
		return ;
	i = x * v.img->bpp / 8 + y * v.img->size_line;
	v.img->img_data[i] = color & 0xFF;
	v.img->img_data[i + 1] = (color & 0xFF00) >> 8;
	v.img->img_data[i + 2] = (color & 0xFF0000) >> 16;
}

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
