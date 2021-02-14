/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:26:58 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/14 16:27:03 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		normelize_angel(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += ((360 * M_PI) / 180);
	return (angle);
}

void		free_player(void *item)
{
	t_player *pla;

	pla = (t_player *)item;
	pla->light_rays.free(&pla->light_rays, &free_ray_sp);
	pla->wall_rays.free(&pla->wall_rays, &free_ray);
	pla->sprit_rays.free(&pla->sprit_rays, &free_ray_sp);
	free(pla->pos);
}
