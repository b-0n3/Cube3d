/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_walls_e.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:20 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:23 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

double		push_e_walls_c(char *arr, t_vector p, char *l)
{
	int len;

	if (p.x < ft_strlen(l))
		while (ft_strchr(arr, l[(int)p.x]) != NULL)
		{
			p.y += 1;
			l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
			if (l == NULL)
				break ;
			len = ft_strlen(l);
			if (p.x >= len)
				break ;
		}
	return (p.y);
}

void		push_e_wall(t_vector start, t_vector p)
{
	if (start.y < p.y)
		g_game->walls.push(&(g_game->walls),
				new_wall(
					new_vector_pointer((start.x + 1) * g_game->wvalue,
						(start.y) * g_game->hvalue),
					new_vector_pointer((p.x + 1) * g_game->wvalue,
						(p.y) * g_game->hvalue), 3), sizeof(t_wall));
}

#ifdef BONUS

void		push_e_walls(t_vector p)
{
	char		*l;
	t_vector	start;
	char		*arr;

	arr = "1s2";
	new_vector(&start, p.x, p.y);
	l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
	while (l != NULL && p.y < g_game->parser->lines.index)
	{
		l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
		p.y = push_e_walls_c(arr, p, l);
		push_e_wall(start, p);
		p.y += 1;
		start.x = p.x;
		start.y = p.y;
	}
}

#else

void		push_e_walls(t_vector p)
{
	char		*l;
	t_vector	start;
	char		*arr;

	arr = "1s";
	new_vector(&start, p.x, p.y);
	l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
	while (l != NULL && p.y < g_game->parser->lines.index)
	{
		l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
		p.y = push_e_walls_c(arr, p, l);
		push_e_wall(start, p);
		p.y += 1;
		start.x = p.x;
		start.y = p.y;
	}
}

#endif
