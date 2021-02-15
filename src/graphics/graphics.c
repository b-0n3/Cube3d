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

void	rec(int pos[], int sizex, int sizey, int color)
{
	int x2;
	int y2;
	int vx;

	y2 = pos[1] + sizey;
	x2 = pos[0] + sizex;
	while (pos[1] < y2)
	{
		vx = pos[0];
		while (vx < x2)
		{
			g_game->window.img->put_pixel(g_game->window, vx, pos[1], color);
			vx++;
		}
		pos[1] += 1;
	}
}

int		rgb_to_int(int r, int g, int b)
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
