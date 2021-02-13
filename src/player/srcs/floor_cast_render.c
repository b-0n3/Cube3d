/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:02 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:48:07 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern t_game *g_game;
t_player *player;

void render_floor(float floorx, float floory,float step[], int y)
{
	int x;
	int  color;
	int tx;
	int ty;

	x = 0;
	while( x < g_game->width)
	{
		tx = ( int)(g_game->floor->width /2 
				* (floorx - floor(floorx)) ) & ( g_game->floor->width -1 );
		ty = (int)(g_game->floor->height /2  
				* (floory - floor(floory)) ) & (g_game->floor->height -1);
		floorx += step[0];
		floory += step[1];
		color = g_game->floor->data[g_game->floor->width * ty + tx];
		color = shadow(color , g_game->heigth  - y);
		if (y > g_game->heigth /2  +  player->offset)
			image_put_pixel(g_game->window , x,y ,color);
		x++;
	}

}

void cast_draw_floor(t_player *this)
{
	float r_dirs[4];
	float steps[2];
	float row_distance;
	t_vector pos;
	int y;

	player = this;
	new_vector(&pos, 0,0);
	y =0;
	while ( y < g_game->heigth)
	{
		r_dirs[0] = this->dir->x - this->planx;
		r_dirs[1] = this->dir->y - this->plany;
		r_dirs[2] = this->dir->x + this->planx;
		r_dirs[3] = this->dir->y + this->plany;
		row_distance = (0.5 * g_game->heigth - this->offset) 
			/ (y - (g_game->heigth / 2) -this->offset);
		steps[0] = (row_distance * (r_dirs[2] - r_dirs[0] ))/ g_game->width;
		steps[1] = (row_distance * (r_dirs[3] - r_dirs[1]) )/ g_game->heigth;
		pos.x =  this->vpos->x + row_distance * r_dirs[0];
		pos.y =  this->vpos->y + row_distance * r_dirs[1];
		render_floor(pos.x,pos.y, steps, y);
		y++;
	}
}

