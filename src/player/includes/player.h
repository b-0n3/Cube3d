/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:47:48 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:47:49 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PLAYER_H
# define FT_PLAYER_H

# include "array_list.h"
# include "vector.h"
# include "ft_line.h"

typedef struct		s_player{
	t_vector		*pos;
	t_vector		*dir;
	t_vector		*vpos;
	double			rotaion_angle;
	double			fov;
	double			rotation_speed;
	double			mov_speed;
	int				w_dir;
	double			side_angle;
	int				t_dir;
	int				offset;
	float			planx;
	float			plany;
	t_array_list	collision;
	t_array_list	wall_rays;
	t_array_list	sprit_rays;
	t_array_list	light_rays;
	void			(*update)(struct s_player *this);
	void			(*render)(struct s_player *this);
	void			(*free)(void *item);
}					t_player;

void				new_player(t_player *this, t_vector *pos, char ch);
void				update_player(t_player *this);
void				render_player(t_player *this);
void				free_player(void *item);
void				s_player_down(t_vector *pos, int newx, int newy);
void				s_player_up(t_vector *pos, int newx, int newy);
void				draw_ray(void *item);
void				cast_rays(void *item);
void				draw_sprit(void *item);
void				cast_draw_floor(t_player *this);
void				update_on_secret_door(t_player *player,
	double newx, double newy);
void				update_secretdor_pos(t_vector *pos, int newx, int newy);
t_bool				check_collision(t_player *player, double newx, double newy);
void				update_player_pos(t_player *player,
	double newx, double newy, double ffangle);
void				update_floor_cords(t_player *player);

#endif
