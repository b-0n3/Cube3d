/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:50:58 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:50:59 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern t_game *game;
void   render_wall_texture(double p[], double wallHei ,t_texture *tex , double dis)
{
	int color;
	t_vector pos;
	int y2;
	float index;

	index = 0;
	new_vector(&pos, p[0],p[1]);
	y2 = p[1]  + wallHei;
	while (pos.y < y2)
	{
		if (((int)tex->offset   + (int) index  * (int)tex->width ) >= tex->height * tex->width)
			break;
		color = tex->data[(int)tex->offset   + (int) index  * (int)tex->width];
		color = shadow (color , dis);
		image_put_pixel(game->window , p[0] , pos.y, color);
		pos.y += 1;
		index += tex->height / wallHei;
	} 
}
