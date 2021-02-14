/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:41 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:48:45 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

void	render_player(t_player *this)
{
	t_ray_sp *spray;

	this->wall_rays.foreach(&this->wall_rays, &cast_rays);
	if (g_game->floor != NULL)
		cast_draw_floor(this);
	this->wall_rays.foreach(&this->wall_rays, &draw_ray);
	while ((spray = (t_ray_sp *)this->light_rays.pull(
			&this->light_rays)) != NULL)
	{
		if (spray != NULL)
			draw_sprit(spray);
	}
	while ((spray = (t_ray_sp *)this->sprit_rays.pull(
			&this->sprit_rays)) != NULL)
	{
		if (spray != NULL)
			draw_sprit(spray);
	}
}
