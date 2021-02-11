/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:51:23 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:51:26 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_wall *new_wall(t_vector *pos , t_vector *dir, int angle)
{
	t_wall *wall;

	wall = (t_wall *)malloc(sizeof(t_wall));
	wall->dir = dir;
	wall->pos = pos;
	wall->kind = angle;
	return wall;
}


