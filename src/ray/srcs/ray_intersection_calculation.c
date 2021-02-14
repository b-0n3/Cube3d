/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection_calculation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:50:15 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:50:17 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_den(t_ray *ray, t_wall wall)
{
	return ((wall.pos->x - wall.dir->x) * (ray->pos->y - ray->dir->y)
		- (wall.pos->y - wall.dir->y) * (ray->pos->x - ray->dir->x));
}

double	calculate_t(t_ray *ray, t_wall wall, double den)
{
	return (((wall.pos->x - ray->pos->x)
			* (ray->pos->y - ray->dir->y)
			- (wall.pos->y - ray->pos->y)
			* (ray->pos->x - ray->dir->x)) / den);
}

double	calculate_u(t_ray *ray, t_wall wall, double den)
{
	return (-((wall.pos->x - wall.dir->x)
			* (wall.pos->y - ray->pos->y)
			- (wall.pos->y - wall.dir->y)
			* (wall.pos->x - ray->pos->x))
			/ den);
}
