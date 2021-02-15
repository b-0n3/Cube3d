/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_walls_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:45 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:48 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game *g_game;

double		push_s_walls_c(char *arr, char *l, char *l_u, t_vector r_p)
{
	while (ft_strchr(arr, l[(int)r_p.x]) != NULL &&
			ft_strchr(arr, l_u[(int)r_p.x]) == NULL)
		r_p.x += 1;
	return (r_p.x);
}

void		push_s_wall(t_vector start, t_vector r_p)
{
	if (start.x < r_p.x)
	{
		g_game->walls.push(&(g_game->walls),
				new_wall(new_vector_pointer(start.x *
				g_game->wvalue, (start.y) * g_game->hvalue),
					new_vector_pointer((r_p.x) *
					g_game->wvalue, (r_p.y) * g_game->hvalue), 2),
				sizeof(t_wall));
	}
}

#ifdef BONUS

void		push_s_walls(t_parser *this, char *l, t_vector r_p)
{
	char		*l_u;
	t_vector	start;
	char		*arr;

	l_u = this->lines.get(&(this->lines), r_p.y - 1);
	arr = "1s2";
	g_game = this->g;
	new_vector(&start, r_p.x, r_p.y);
	if (l_u != NULL)
		while ((int)r_p.x < (int)ft_strlen(l) &&
			(int)r_p.x < (int)ft_strlen(l_u))
		{
			r_p.x = push_s_walls_c(arr, l, l_u, r_p);
			push_s_wall(start, r_p);
			r_p.x += 1;
			start.x = r_p.x;
			start.y = r_p.y;
		}
}

#else

void		push_s_walls(t_parser *this, char *l, t_vector r_p)
{
	char		*l_u;
	t_vector	start;
	char		*arr;

	l_u = this->lines.get(&(this->lines), r_p.y - 1);
	arr = "1s";
	g_game = this->g;
	new_vector(&start, r_p.x, r_p.y);
	if (l_u != NULL)
		while ((int)r_p.x < (int)ft_strlen(l) &&
			(int)r_p.x < (int)ft_strlen(l_u))
		{
			r_p.x = push_s_walls_c(arr, l, l_u, r_p);
			push_s_wall(start, r_p);
			r_p.x += 1;
			start.x = r_p.x;
			start.y = r_p.y;
		}
}

#endif
