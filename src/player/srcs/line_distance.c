/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:15 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:48:17 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		calculate_t_sprite(t_ray_sp *ray, t_line line, double den)
{
	return ((line.pos->x - ray->pos->x)
			* (ray->pos->y - ray->dir->y)
			- (line.pos->y - ray->pos->y)
			* (ray->pos->x - ray->dir->x)) / den;
}

double		calculate_u_sprite(t_ray_sp *ray, t_line line, double den)
{
	return (-((line.pos->x - line.dir->x)
			* (line.pos->y - ray->pos->y)
			- (line.pos->y - line.dir->y)
			* (line.pos->x - ray->pos->x))
			/ den);
}

double		calculate_den_sprite(t_ray_sp *ray, t_line line)
{
	return ((line.pos->x - line.dir->x)
			* (ray->pos->y - ray->dir->y)
			- (line.pos->y - line.dir->y)
			* (ray->pos->x - ray->dir->x));
}

double		get_offset(t_line tang, t_ray_sp *ray)
{
	double	den;
	float	t;
	float	u;

	t = 0;
	u = 0;
	den = calculate_den_sprite(ray, tang);
	free(tang.dir);
	if (den != 0)
	{
		t = calculate_t_sprite(ray, tang, den);
		u = calculate_u_sprite(ray, tang, den);
		return (t * ray->sp->rad);
	}
	return (0);
}

double		get_line_distance(t_ray_sp *ray)
{
	t_line	tang;
	double	angle;

	tang.pos = ray->sp->pos;
	angle = normelize_angel(atan2(ray->pos->y - tang.pos->y,
				ray->pos->x - tang.pos->x)) + M_PI_2;
	angle = normelize_angel(angle);
	tang.dir = new_vector_pointer(tang.pos->x + (ray->sp->rad * cos(angle)),
			tang.pos->y + (ray->sp->rad * sin(angle)));
	return (get_offset(tang, ray));
}
