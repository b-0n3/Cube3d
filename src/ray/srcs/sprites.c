/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:53:16 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:53:19 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int g_nb_rays;

t_vector	*get_sprite_inter
	(t_vector *pos, t_vector *dir, t_vector *c_pos, double rad)
{
	double	ab_scaling_factor;
	double	a;
	double	bby2;
	double	c;
	double	disc;

	a = (dir->x - pos->x) * (dir->x - pos->x) +
		(dir->y - pos->y) * (dir->y - pos->y);
	bby2 = (dir->x - pos->x) * (c_pos->x - pos->x) +
		(dir->y - pos->y) * (c_pos->y - pos->y);
	c = (c_pos->x - pos->x) * (c_pos->x - pos->x) +
		(c_pos->y - pos->y) * (c_pos->y - pos->y) - rad * rad;
	disc = (bby2 / a) * (bby2 / a) - (c / a);
	if (disc < 0)
		return (NULL);
	ab_scaling_factor = -(bby2 / a) + sqrt(disc);
	if (ab_scaling_factor <= 0)
	{
		return (new_vector_pointer(pos->x - (dir->x - pos->x) *
				ab_scaling_factor,
				pos->y - (dir->y - pos->y) * ab_scaling_factor));
	}
	return (NULL);
}

void		cast_sprite
	(t_vector *pos, t_sprites *sp, t_ray_sp **ray_sp, t_ray *ray)
{
	t_vector	*in;
	t_vector	sub;
	double		splen;
	t_vector	*dir;

	dir = new_vector_pointer(pos->x + ray->length(ray) *
		cos(ray->angle), pos->y + ray->length(ray) * sin(ray->angle));
	in = get_sprite_inter(pos, dir, sp->pos, sp->rad);
	free(dir);
	if (in != NULL)
	{
		new_vector(&sub, pos->x - in->x, pos->y - in->y);
		splen = sub.length(&sub);
		if (splen < ray->length(ray))
		{
			if (*ray_sp == NULL)
				*ray_sp = new_sp_ray((t_vector **){pos, in},
					ray->angle, ray->index, sp);
			else if (splen < (*ray_sp)->length(*ray_sp))
				(*ray_sp)->update(*ray_sp, in, sp);
		}
		free(in);
	}
	free(pos);
}

double		get_angle(double x, double y)
{
	double res;

	if (y < 0 || x < 0)
		return (0);
	res = x / y;
	return (atan(res));
}

t_sprites	*new_sprite(t_vector *pos, double rad, int kind)
{
	double		angle;
	t_sprites	*sp;

	sp = (t_sprites *)malloc(sizeof(t_sprites));
	sp->pos = pos;
	sp->rad = rad;
	sp->kind = kind;
	sp->free = &free_sprite;
	sp->d_a = get_angle(sp->pos->x, sp->pos->y + rad);
	sp->u_a = get_angle(sp->pos->x, sp->pos->y - rad);
	angle = sp->u_a - sp->d_a;
	sp->a_p_r = angle / g_nb_rays;
	return (sp);
}
