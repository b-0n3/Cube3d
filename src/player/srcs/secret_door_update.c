/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_door_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:49:06 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:49:08 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *g_game;

void	s_player_right(t_vector *pos, int newx, int newy)
{
	char	*line;
	int		i;

	i = newx;
	line = (char *)g_game->parser->lines.get(&g_game->parser->lines, newy);
	if (line != NULL)
	{
		while (line[i] == 's')
			i++;
		if (line[i] == '0')
		{
			pos->y = (newy + 0.5) * g_game->hvalue;
			pos->x = (i + 0.5) * g_game->hvalue;
		}
	}
}

void	s_player_left(t_vector *pos, int newx, int newy)
{
	char	*line;
	int		i;

	i = newx;
	line = (char *)g_game->parser->lines.get(&g_game->parser->lines, newy);
	if (line != NULL)
	{
		while (i > 0 && line[i] == 's')
			i--;
		if (line[i] == '0')
		{
			pos->y = (newy + 0.5) * g_game->hvalue;
			pos->x = (i + 0.5) * g_game->hvalue;
		}
	}
}

void	s_player_down(t_vector *pos, int newx, int newy)
{
	char	*line;
	int		i;
	t_bool	comp;

	comp = FALSE;
	i = newy;
	while (!comp)
	{
		line = (char *)g_game->parser->lines.get(&g_game->parser->lines, i);
		if (line == NULL
				|| (check_empty_line(line) || newx > (int)ft_strlen(line)))
			break ;
		if (ft_strchr("s0", line[newx]) == NULL)
			break ;
		if (line[newx] == '0')
		{
			pos->y = (i + 0.5) * g_game->hvalue;
			pos->x = (newx + 0.5) * g_game->hvalue;
			comp = TRUE;
		}
		i++;
	}
}

void	s_player_up(t_vector *pos, int newx, int newy)
{
	char	*line;
	int		i;
	t_bool	comp;

	comp = FALSE;
	i = newy;
	while (!comp)
	{
		line = (char *)g_game->parser->lines.get(&g_game->parser->lines, i);
		if (line == NULL ||
			(check_empty_line(line) || newx > (int)ft_strlen(line)))
			break ;
		if (ft_strchr("s0", line[newx]) == NULL)
			break ;
		if (line[newx] == '0')
		{
			pos->y = (i + 0.5) * g_game->hvalue;
			pos->x = (newx + 0.5) * g_game->hvalue;
			comp = TRUE;
		}
		i--;
	}
}

void	update_secretdor_pos(t_vector *pos, int newx, int newy)
{
	int	posx;
	int	posy;

	posx = pos->x / g_game->hvalue;
	posy = pos->y / g_game->hvalue;
	if (posy > newy)
		s_player_up(pos, newx, newy);
	else if (posy < newy)
		s_player_down(pos, newx, newy);
	else if (posx < newx)
		s_player_right(pos, newx, newy);
	else if (posx > newx)
		s_player_left(pos, newx, newy);
}
