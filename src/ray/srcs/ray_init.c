/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:50:02 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:50:03 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray_sp *new_sp_ray(t_vector *pos, t_vector *dir,  double angle, int i, t_sprites *sp)
{
	t_ray_sp *ray;

	ray = (t_ray_sp *)malloc(sizeof (t_ray_sp));
	if (ray != NULL)
	{
		ray->pos = new_vector_pointer(pos->x, pos->y);
		ray->cast = &cast_ray;
		ray->length = &ray_sp_len;
		ray->free = &free_ray_sp;
		ray->update = &update_sp_ray;
		ray->dir = NULL;
		ray->angle = angle;
		ray->index = i;
		ray->update(ray, dir, sp);
	}
	return ray;
}

t_ray *new_ray(t_vector *pos, double angle, int i)
{
	t_ray *ray;

	ray = (t_ray *)malloc(sizeof (t_ray));
	if (ray != NULL)
	{
		ray->pos = pos;
		ray->update = &update_ray;
		ray->render = &render_ray;
		ray->cast = &cast_ray;
		ray->free = &free_ray;
		ray->length = &ray_len;
		ray->dir = NULL;
		ray->update(ray , angle, i);
		ray->coli = 0;
	}

	return ray;
}
