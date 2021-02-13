/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:32 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:48:34 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game   *g_game;
int             nb_rays;

void set_rotation_angle(t_player *this, char ch)
{
	if (ch == 'S')
		this->rotaion_angle =  (M_PI_2);
	else if (ch == 'N')
		this->rotaion_angle =  (3 * M_PI_2);
	else if (ch == 'W')
		this->rotaion_angle = M_PI;
	else
		this->rotaion_angle = 0.0f;
}
void init_player_lists(t_player *this)
{
	new_array_list(&(this->collision), 1, sizeof(t_ray));
	new_array_list(&(this->wall_rays) ,nb_rays, sizeof (t_ray));
	new_array_list(&(this->sprit_rays) ,14, sizeof (t_ray));
	new_array_list(&(this->light_rays) ,14, sizeof (t_ray_sp));
	this->collision.push(&(this->collision),new_ray(this->pos , this->rotaion_angle , -10 ) , sizeof(t_ray));
}
void init_wall_rays(t_player *this)
{
	double  ray_angle;
	int     nb;

	ray_angle = this->rotaion_angle - (this->fov / 2);
	nb = 0;
	while (nb < nb_rays)
	{
		ray_angle = normelize_angel(ray_angle);
		this->wall_rays.push(&this->wall_rays, new_ray(this->pos ,ray_angle,nb) , sizeof(t_ray));
		ray_angle = ray_angle + (this->fov / nb_rays);
		nb++;
	}
}
void new_player(t_player *this , t_vector *pos, char ch)
{
	this->fov = 70 * (M_PI / 180);
	this->render= &render_player;
	this->pos = pos;
	this->vpos = new_vector_pointer(pos->x, pos->y);
	this->mov_speed =8;
	this->update = &update_player;
	this->side_angle = 0;
	this->rotation_speed = this->mov_speed  * 0.0154533;
	this->w_dir = 0;
	this->t_dir = 0;
	this->offset = 0;
	this->planx = 0;
	this->plany = 0.66;
	this->free = &free_player;
	nb_rays = g_game->width - 2;
	set_rotation_angle(this, ch);
	this->dir = new_vector_pointer(-1, 0);
	init_player_lists(this);
	init_wall_rays(this);
}
