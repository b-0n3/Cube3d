/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:44:48 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:44:49 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game	*g_game;

void		push_sprite(int x, int y, float size, char ch)
{
	g_game->sprites.push(&g_game->sprites,
			new_sprite(new_vector_pointer((x + 0.5) * g_game->wvalue,
			(y + 0.5) * g_game->hvalue), size * 0.3, ch - 48),
			sizeof(t_sprites));
}

void		check_and_push_sprite(char *arr, char *l, int x, int y)
{
	t_sp_texture	*tex;
	float			size;

	size = g_game->wvalue;
	if (ft_strchr(arr, l[x]) == NULL)
	{
		tex = get_sp_tex(l[x] - 48);
		if (tex != NULL)
		{
			if (tex->wsize < size)
				size = tex->wsize;
			push_sprite(x, y, size, l[x]);
		}
	}
}

void		check_and_push_lights(char *l, int x, int y)
{
	t_sp_texture	*tex;

	if (l[x] == '5')
	{
		tex = get_sp_tex(l[x] - 48);
		if (tex != NULL)
		{
			g_game->lights.push(&g_game->lights,
					new_sprite(new_vector_pointer((x + 0.5) * g_game->wvalue,
					(y + 0.5) * g_game->hvalue),
					0.19 * g_game->hvalue, l[x] - 48), sizeof(t_sprites));
		}
	}
}

#ifdef BONUS

void		get_sprites(t_parser *this)
{
	int		x;
	size_t	y;
	char	*l;
	char	*arr;

	arr = "12s5";
	y = 0;
	while (y < this->lines.index)
	{
		x = 0;
		l = this->lines.get(&this->lines, y);
		while (l[x] != '\0')
		{
			check_and_push_sprite(arr, l, x, y);
			check_and_push_lights(l, x, y);
			x++;
		}
		y++;
	}
}

#else

void		get_sprites(t_parser *this)
{
	int		x;
	size_t	y;
	char	*l;
	char	*arr;

	arr = "1s5";
	y = 0;
	while (y < this->lines.index)
	{
		x = 0;
		l = this->lines.get(&this->lines, y);
		while (l[x] != '\0')
		{
			check_and_push_sprite(arr, l, x, y);
			check_and_push_lights(l, x, y);
			x++;
		}
		y++;
	}
}

#endif
