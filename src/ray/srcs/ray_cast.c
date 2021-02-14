/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:49:48 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:49:49 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

void	cast_rays(void *item)
{
	t_ray *ray;

	ray = (t_ray *)item;
	if (ray != NULL)
	{
		ray->cast(ray);
	}
}

void	cast_sprite_s(t_ray *ray)
{
	size_t		index;
	t_ray_sp	*sp;
	t_sprites	*spp;

	sp = NULL;
	spp = NULL;
	index = 0;
	while (index < g_game->sprites.index)
	{
		spp = g_game->sprites.get(&g_game->sprites, index);
		cast_sprite(new_vector_pointer(ray->pos->x, ray->pos->y), spp,
				&sp, ray);
		index++;
	}
	if (sp != NULL)
		g_game->player.sprit_rays.push(
				&(g_game->player.sprit_rays), sp, sizeof(t_ray_sp));
}

void	cast_lights(t_ray *ray)
{
	size_t		index;
	t_ray_sp	*sp;
	t_sprites	*spp;

	sp = NULL;
	spp = NULL;
	if (ray->index != -10)
	{
		index = 0;
		while (index < g_game->lights.index)
		{
			spp = g_game->lights.get(&g_game->lights, index);
			cast_sprite(new_vector_pointer(ray->pos->x, ray->pos->y), spp,
					&sp, ray);
			index++;
		}
		if (sp != NULL)
			g_game->player.light_rays.push(
					&(g_game->player.light_rays), sp, sizeof(t_ray_sp));
	}
}

void	cast_ray(void *r)
{
	size_t	index;
	t_wall	wall;
	t_ray	*ray;

	ray = (t_ray *)r;
	index = 0;
	while (index < g_game->walls.index)
	{
		wall = *((t_wall *)g_game->walls.get(&g_game->walls, index));
		get_intesection_wall(ray, wall);
		index++;
	}
	cast_sprite_s(ray);
	cast_lights(ray);
}
