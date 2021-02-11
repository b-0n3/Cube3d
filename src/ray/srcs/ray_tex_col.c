/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tex_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:51:08 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:51:11 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern t_game *game;

// int pick_color(int kind, double correctdis)
// {
//   int color;

//             if (kind == 0 )
//             color = shadow(game->color[0] , correctdis);
//             else  if (kind == 1)
//             color = shadow(game->color[1] , correctdis) ;
//             else  if (kind == 2)
//             color = shadow(game->color[2] , correctdis) ;
//             else  if (kind == 3)         
//             color = shadow(game->color[3] , correctdis);
//     return color;
// }

t_texture   *pick_texture(int kind)
{
	t_texture *tex;

	tex = NULL;
	if (kind == 2 && game->n_texture != NULL)
		tex = game->n_texture;
	else  if (kind == 0  && game->so_texture != NULL)
		tex = game->so_texture;
	else  if (kind == 3 && game->ea_texture != NULL)
		tex = game->ea_texture;
	else if (kind == 1 && game->we_texture != NULL)         
		tex = game->we_texture;
	return tex;
}
