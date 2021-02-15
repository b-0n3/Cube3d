/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:58:32 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/13 16:58:36 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include <mlx.h>
# include "get_next_line.h"
# include "array_list.h"
# include "ray.h"
# include "player.h"
# include "parser.h"
# include "ft_line.h"
# include "game.h"

double	get_line_distance(t_ray_sp *ray);
void	draw_line(t_window wi, t_vector *pos, t_vector *dir, int color);
void	draw_rec(t_window wi, t_vector pos, int size, int color);
void	ft_line(float x, float y, int size, float angle, int color);
void	image_put_pixel(t_window v, int x, int y, int color);
void	rec(int pos[], int sizex, int sizey, int color);
int		shadow(int color, double distance);
int		key_pressed(int k_code, void *ptr);
int		key_relased(int k_code, void *ptr);
int		mouse_pressed(int button, int x, int y, void *param);
int		mouse_relased(int button, int x, int y, void *param);
#endif
