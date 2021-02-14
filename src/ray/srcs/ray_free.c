/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:49:55 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:49:56 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_ray(void *item)
{
	t_ray *ray;

	ray = (t_ray *)item;
	if (ray != NULL)
	{
		if (ray->dir != NULL)
		{
			free(ray->dir);
		}
		free(ray);
	}
}

void	free_sprite(void *item)
{
	t_sprites *sp;

	sp = (t_sprites *)item;
	if (sp != NULL)
	{
		free(sp->pos);
		free(sp);
	}
}

void	free_wall(void *item)
{
	t_wall *wall;

	wall = (t_wall *)item;
	if (wall != NULL)
	{
		if (wall->dir != NULL)
			free(wall->dir);
		if (wall->pos != NULL)
			free(wall->pos);
		free(wall);
	}
}

void	free_ray_sp(void *item)
{
	t_ray_sp *ray;

	ray = (t_ray_sp*)item;
	if (ray != NULL)
	{
		if (ray->dir != NULL)
			free(ray->dir);
		if (ray->pos != NULL)
			free(ray->pos);
		free(ray);
	}
}
