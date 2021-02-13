/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:59 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:49:01 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern t_game *g_game;
void   render_sprite_texture(double p[] , double wallHei ,t_sp_texture *tex , double dis)
{
	int color;
	t_vector pos;
	int y2;
	float i_step[3];

	i_step[0] = 0;
	y2 = p[1]  + wallHei;
	i_step[1]  = tex->height / wallHei;
	new_vector(&pos,  p[0], p[1]);
	while (pos.y < y2)
	{
		i_step[2] = (int) tex->offset    + (int) i_step[0]  * (int)tex->width;
		if (i_step[2] < (tex->height * tex->width))
		{
			color = tex->data[(int) i_step[2]];
			if(color > 0)
				if (!(tex->kind == '5' - 48 && color == tex->data[0]))
				{
					if (tex->kind != '5' - 48 && tex->kind != 10)
						color = shadow(color , dis);
					image_put_pixel(g_game->window , p[0] , pos.y, color);
				}
		}
		pos.y += 1;
		i_step[0]  += i_step[1];
	}
}
