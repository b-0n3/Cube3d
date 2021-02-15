/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:34:58 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/15 15:35:02 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

double		length(t_vector *this)
{
	return ((double)sqrt((this->x * this->x) + (this->y * this->y)));
}

void		add(t_vector *this, t_vector *o)
{
	this->x += o->x;
	this->y += o->y;
	this->len = this->length(this);
}

void		sub(t_vector *this, t_vector *o)
{
	this->x -= o->x;
	this->y -= o->y;
	this->len = this->length(this);
}

t_bool		con(void *item)
{
	t_vector *vert1;

	vert1 = (t_vector *)item;
	if (vert1->len <= 4.0f)
		return (TRUE);
	return (FALSE);
}

int			compare_to(void *this, void *o)
{
	if (((t_vector *)this)->len < ((t_vector *)o)->len)
		return (1);
	if (((t_vector *)this)->len > ((t_vector *)o)->len)
		return (-1);
	return (0);
}
