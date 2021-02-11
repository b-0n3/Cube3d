/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:53:35 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:53:38 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *game;

t_vector new_vector(t_vector *this,double x, double y)
{
	this->x = x;
	this->y = y;
	this->length = &length;
	this->add = &add;
	this->sub = &sub;
	this->get_dir_angle = &dir_from_angle;
	this->len = this->length(this);
	this->compare_to  = &compare_to;
	this->to_string = &vector_to_string;
	return *this;
}
t_vector *new_vector_pointer(double x, double y)
{
	t_vector *this;

	this = (t_vector *)malloc(sizeof(t_vector));
	if (this != NULL)
	{
		this->x = x;
		this->y = y;
		this->length = &length;
		this->add = &add;
		this->sub = &sub;
		this->get_dir_angle = &dir_from_angle;
		this->len = this->length(this);
		this->compare_to  = &compare_to;
		this->to_string = &vector_to_string;
		return (this);
	}
	return NULL;
}

double length(t_vector *this)
{
	return ((double) sqrt((this->x * this-> x) + (this->y * this->y)));
}

void add(t_vector *this , t_vector *o)
{
	this->x += o->x;
	this->y += o->y;
	this->len = this->length(this);
}

void sub(t_vector *this, t_vector *o)
{
	this->x -= o->x;
	this->y -= o->y;
	this->len = this->length(this);
}

t_bool con(void *item)
{
	t_vector *vert1 = (t_vector *) item;
	if (vert1-> len  <= 4.0f)
		return TRUE;
	return FALSE;
}


int compare_to(void  *this , void *o)
{
	if (((t_vector *) this)->len < ((t_vector *)o)->len)
		return  1;
	if (((t_vector *) this)->len > ((t_vector *)o)->len)
		return  -1;
	return 0;
}

void vector_to_string(void *item)
{
	item = NULL;
}

t_vector *dir_from_angle(t_vector *this, double angle)
{
	return (new_vector_pointer(this->x + 
				(game->wvalue/2 * cos(angle)) , 
				this->y + (game->hvalue/2 * sin(angle))));
}


