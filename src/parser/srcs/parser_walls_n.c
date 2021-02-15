/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_walls_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:29 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:35 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

double		push_n_walls_c(char *arr, t_vector r_p, char *l, char *l_d)
{
	while (ft_strchr(arr, l[(int)r_p.x]) != NULL
			&& ft_strchr(arr, l_d[(int)r_p.x]) == NULL)
	{
		if (l[(int)r_p.x] == '\0' || l_d[(int)r_p.x] == '\0')
			break ;
		r_p.x += 1;
	}
	return (r_p.x);
}

void		push_n_wall(t_vector start, t_vector r_p)
{
	if (start.x < r_p.x)
		g_game->walls.push(&(g_game->walls),
				new_wall(
					new_vector_pointer(start.x * g_game->wvalue, (start.y + 1)
						* g_game->hvalue),
					new_vector_pointer((r_p.x) * g_game->wvalue, (r_p.y + 1)
						* g_game->hvalue), 0), sizeof(t_wall));
}

void		push_player(char *l, t_vector r_p)
{
	char *arr;

	arr = "NSEW";
	if (ft_strchr(arr, l[(int)r_p.x]) != NULL && l[(int)r_p.x] != '\0')
	{
		if (g_game->player.free != NULL)
			put_error(g_game, ft_strjoin("diplicate player pos at line\n", l));
		else
		{
			new_player(&(g_game->player),
					new_vector_pointer(r_p.x * g_game->wvalue +
						(0.5 * g_game->wvalue), r_p.y *
						g_game->hvalue + (0.5 * g_game->hvalue)),
					l[(int)r_p.x]);
			l[(int)r_p.x] = '0';
		}
	}
}

#ifdef BONUS

void		push_n_walls(t_parser *this, char *l, t_vector r_p)
{
	char		*l_d;
	t_vector	start;
	char		*arr;

	arr = "1s2";
	g_game = this->g;
	new_vector(&start, r_p.x, r_p.y);
	l_d = this->lines.get(&(this->lines), r_p.y + 1);
	if (l_d != NULL)
		while ((int)r_p.x < (int)ft_strlen(l) &&
			(int)r_p.x < (int)ft_strlen(l_d))
		{
			r_p.x = push_n_walls_c(arr, r_p, l, l_d);
			push_n_wall(start, r_p);
			push_player(l, r_p);
			r_p.x += 1;
			start.x = r_p.x;
			start.y = r_p.y;
		}
}

#else

void		push_n_walls(t_parser *this, char *l, t_vector r_p)
{
	char		*l_d;
	t_vector	start;
	char		*arr;

	arr = "1s";
	g_game = this->g;
	new_vector(&start, r_p.x, r_p.y);
	l_d = this->lines.get(&(this->lines), r_p.y + 1);
	if (l_d != NULL)
		while ((int)r_p.x < (int)ft_strlen(l) &&
				(int)r_p.x < (int)ft_strlen(l_d))
		{
			r_p.x = push_n_walls_c(arr, r_p, l, l_d);
			push_n_wall(start, r_p);
			push_player(l, r_p);
			r_p.x += 1;
			start.x = r_p.x;
			start.y = r_p.y;
		}
}

#endif
