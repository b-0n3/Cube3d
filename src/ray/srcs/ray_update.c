/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:51:16 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:51:17 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_sp_ray(t_ray_sp *this, t_vector *dir, t_sprites *sp)
{

	if (dir == NULL || sp == NULL)
		return ;
	if(this->dir != NULL)
		free(this->dir);
	this->dir = new_vector_pointer(dir->x, dir->y);
	this->sp = sp;
}

void update_ray(t_ray *this, double angle, int i)
{
	this->index = i;
	this->angle = angle;
	if(this->dir != NULL)
		free(this->dir);
	this->dir = this->pos->get_dir_angle(this->pos, this->angle);
	this->kind = -1;
	this->len = this->length(this);
}
