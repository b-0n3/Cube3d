/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:50:45 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:50:48 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

void	draw_ray(void *item)
{
	t_ray *ray;

	ray = (t_ray *)item;
	if (ray != NULL)
		ray->render(ray);
}

void	render_wall_normal
	(t_ray *this, double end, double wall_hei, double correctdis)
{
	t_texture *tex;

	tex = pick_texture(this->kind);
	if (tex != NULL)
	{
		tex->offset = (this->kind == 0 || this->kind == 2)
		? fmod(this->dir->x, g_game->wvalue)
			: fmod(this->dir->y, g_game->wvalue);
		tex->offset = (tex->offset / g_game->wvalue) * tex->width;
		render_wall_texture((double[]){this->index, end},
			wall_hei, tex, correctdis);
	}
}

void	render_wall_pic
	(t_ray *this, double end, double wall_hei, double correctdis)
{
	t_sp_texture	*text;
	char			*line;
	int				y;
	int				x;

	text = NULL;
	y = ((this->dir->y / g_game->hvalue) - 1) +
		((this->kind == 2 || this->kind == 0) ? 1 : 0);
	x = ((this->dir->x / g_game->hvalue) - 1) + (this->kind == 1 ? 1 : 0);
	line = (char *)g_game->parser->lines.get(
			&g_game->parser->lines, y);
	if (line != NULL && line[x] == '2')
		text = get_sp_tex(2);
	if (text != NULL)
	{
		text->offset = ((this->kind == 0 || this->kind == 2) ?
				fmod(this->dir->x, g_game->wvalue)
				: fmod(this->dir->y, g_game->wvalue))
			+ g_game->hvalue / text->width;
		text->offset = fmod(text->offset, g_game->hvalue);
		text->offset = fabs(text->offset);
		render_sprite_texture((double[]){this->index, end}, wall_hei,
				text, correctdis);
	}
	else
		render_wall_normal(this, end, wall_hei, correctdis);
}

#ifdef BONUS

void	render_ray(t_ray *this)
{
	double dispro;
	double wall_hei;
	double correctdis;
	double end;

	if (this->kind >= 0)
	{
		correctdis = this->length(this) *
			cos(this->angle - g_game->player.rotaion_angle);
		dispro = (g_game->width / 4) * tan(g_game->player.fov);
		wall_hei = (g_game->wvalue / correctdis) * dispro;
		end = ((g_game->heigth / 2) - (wall_hei / 2));
		if (g_game->floor == NULL)
			rec((int[]){this->index, end + wall_hei + g_game->player.offset},
				1, g_game->heigth / 2 - g_game->player.offset,
					g_game->color[4]);
		rec((int[]){this->index, 0}, 1, g_game->heigth - end - wall_hei
			+ g_game->player.offset, g_game->color[5]);
		end += g_game->player.offset;
		render_wall_pic(this, end, wall_hei, correctdis);
	}
}

#else

void	render_ray(t_ray *this)
{
	double dispro;
	double wall_hei;
	double correctdis;
	double end;

	if (this->kind >= 0)
	{
		correctdis = this->length(this) *
			cos(this->angle - g_game->player.rotaion_angle);
		dispro = (g_game->width / 4) * tan(g_game->player.fov);
		wall_hei = (g_game->wvalue / correctdis) * dispro;
		end = ((g_game->heigth / 2) - (wall_hei / 2));
		if (g_game->floor == NULL)
			rec((int[]){this->index, end + wall_hei + g_game->player.offset}, 1,
					g_game->heigth / 2 - g_game->player.offset,
					g_game->color[4]);
		rec(((int *){this->index, 0}), 1, g_game->heigth - end - wall_hei
			+ g_game->player.offset, g_game->color[5]);
		end += g_game->player.offset;
		render_wall_normal(this, end, wall_hei, correctdis);
	}
}

#endif
