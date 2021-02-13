/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check_collision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:25 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:48:27 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;
int tos;

void update_floor_cords(t_player *player)
{
	float     lastplanx;
	double    olddirx;

	player->vpos->x += player->planx * ((player->mov_speed ) *  -player->w_dir);
	player->vpos->y += player->plany * ((player->mov_speed )* -player->w_dir);

	if (player->t_dir != 0)
	{
		lastplanx  = player->planx;
		player->planx = player->planx * cos((player->rotation_speed  * -player->t_dir ))
			- player->plany * sin(( player->rotation_speed  * -player->t_dir ));
		player->plany = lastplanx * sin( player->rotation_speed * -player->t_dir) 
			+ player->plany * cos( player->rotation_speed * -player->t_dir); 
		olddirx = player->dir->x;
		player->dir->x = player->dir->x * cos(player->rotation_speed * -player->t_dir)
			- player->dir->y * sin(player->rotation_speed * -player->t_dir);
		player->dir->y = olddirx *  sin(player->rotation_speed* -player->t_dir)
			+ player->dir->y * cos(player->rotation_speed  * -player->t_dir);
	}
}

void update_player_pos(t_player *player, double newx, double newy, double ffangle)
{


	player->pos->x = newx * g_game->wvalue;
	player->pos->y = newy * g_game->hvalue;
	player->rotaion_angle = ffangle;
	update_floor_cords(player);


}


void update_on_secret_door(t_player *player, double newx, double newy)
{
	char *line;

	line = (char *)g_game->parser->lines.get(
			&g_game->parser->lines, 
			(int)newy);
	if(line != NULL)
		if (newx > 0 && newx < ft_strlen(line))
			if ( line [(int) newx] == 's')
				update_secretdor_pos(player->pos , (int )newx,(int) newy);
}

double  update_player_angle(t_player *player,t_ray **ray)
{
	double new_angle;
	double ffangle;

	new_angle = player->rotaion_angle +( player->w_dir == -1 ? M_PI: 0);  
	new_angle += player->t_dir * player->rotation_speed;
	ffangle = player->rotaion_angle + player->t_dir * player->rotation_speed;
	normelize_angel(new_angle);
	(*ray) = player->collision.get( &player->collision ,0);
	(*ray)->angle = new_angle;
	free((*ray)->dir);
	(*ray)->dir =(*ray)->pos->get_dir_angle((*ray)->pos , (*ray)->angle);
	(*ray)->cast((*ray));
	return ffangle;
}

void update_player_dir(t_player *player,char *line,t_ray *ray, double ffangle)
{
	double newx;

	newx = player->pos->x + (cos(player->rotaion_angle)* player->mov_speed);

	if(line[(int) (newx / g_game->hvalue)] != 's')
		player->rotaion_angle = ffangle;
	ray->coli = 0;
}

t_bool check_collision(t_player *player , double newx ,double newy)
{
	t_ray *ray;
	double ffangle;
	char *line;

	if (tos == 0)
		tos = 1;
	ffangle = update_player_angle(player, &ray);
	line = ((char *)g_game->parser->lines.get(&g_game->parser->lines, (int)newy));
	if(ray->coli == 1 || ft_strchr("50",line [(int) newx ]) == NULL)
	{
		if (player->t_dir != 0)
			tos = player->t_dir;
		update_player_dir(player,line,ray,ffangle);
		update_on_secret_door(player, newx, newy);
		return TRUE;
	}
	else
		update_player_pos(player,newx,newy,ffangle);
	return FALSE;
}
