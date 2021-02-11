/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:49:13 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:49:15 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern t_game *game;

void render_sprite_c(t_ray_sp *this,double end , double wall_hei,double correctdis)
{
	t_line tang;
	double angle;
	t_sp_texture *tsp;

	tsp = get_sp_tex(this->sp->kind);
	tang.pos = this->sp->pos;
	angle = normelize_angel(atan2(this->pos->y - tang.pos->y , 
				this->pos->x - tang.pos->x))  + M_PI_2;
	angle = normelize_angel(angle);
	tang.dir = new_vector_pointer(tang.pos->x + (this->sp->rad * cos(angle)), 
			tang.pos->y + (this->sp->rad * sin (angle )));
	double dist =  get_line_distance(this) ;
	dist += this->sp->rad;
	if (tsp != NULL)
	{
		double nof = (dist / (2 * this->sp->rad)) * tsp->wsize;
		tsp->offset = nof + tsp->borders[2];
		tsp->offset = fabs(tsp->offset);
		render_sprite_texture((double []){this->index, end}, wall_hei, tsp, correctdis);
	}
}

void  draw_sprit(void *item)
{
	t_ray_sp *this = (t_ray_sp *) item;

	double dispro;
	double wall_hei;
	double correctdis;
	double end;
	if(this->pos != NULL  && this->sp != NULL)
	{
		correctdis = this->length(this) * cos(this->angle -game->player.rotaion_angle);
		dispro = (game->width / 4) * tan(game->player.fov );
		wall_hei = (game->wvalue / correctdis) * dispro;
		end = game->heigth /2  - wall_hei / 2;
		end += game->player.offset;
		render_sprite_c(this, end, wall_hei, correctdis);
	}
	free_ray_sp(this);
}
