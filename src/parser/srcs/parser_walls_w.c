/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_walls_w.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:53 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:54 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern t_game *g_game;

double push_w_walls_c(char *arr , char *l, t_vector p)
{
	int len;
	if (p.x < ft_strlen(l))
		while (ft_strchr(arr, l[(int) p.x]) != NULL&& 
				ft_strchr(arr , l[(int)p.x - 1] ) == NULL)
		{
			p.y += 1;
			l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
			if (l == NULL)
				break;
			len = ft_strlen(l);
			if (p.x >= len)
				break;

		}
	return p.y;
}
void push_w_wall(t_vector start , t_vector p)
{
	if (start.y < p.y)
	{

		g_game->walls.push(&(g_game->walls),
				new_wall(new_vector_pointer((start.x ) * g_game->wvalue,
						(start.y )*g_game->hvalue),
					new_vector_pointer((p.x)* g_game->wvalue ,
						(p.y )*g_game->hvalue),1), sizeof(t_wall));
	}
}

void push_w_walls(t_vector p)
{
	char *l;
	t_vector start;
	char *arr;

#ifdef BONUS

	arr =  "1s2";
#else

	arr = "1s";
#endif
	l = g_game->parser->lines.get(&g_game->parser->lines, p.y);
	new_vector(&start , p.x, p.y);
	while (l != NULL && p.y < g_game->parser->lines.index)
	{
		l = g_game->parser->lines.get(&g_game->parser->lines, p.y );
		p.y = push_w_walls_c(arr ,l , p);
		push_w_wall(start ,p);
		p.y += 1;
		start.x = p.x;
		start.y = p.y;

	}
}
