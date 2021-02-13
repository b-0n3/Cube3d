/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:47:16 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:47:24 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game		*g_game;

t_bool		check_empty_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '#')
		return (TRUE);
	while (line[i] != '\0')
	{
		if (!ft_iswhitespace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void		init_tex(void)
{
	g_game->ea_texture = NULL;
	g_game->n_texture = NULL;
	g_game->so_texture = NULL;
	g_game->we_texture = NULL;
	g_game->color[0] = 0xf8b400;
	g_game->color[1] = 0x2c786c;
	g_game->color[2] = 0xbb3b0e;
	g_game->color[3] = 0xdd7631;
	g_game->color[4] = 0xbb3b0e;
	g_game->color[5] = 0x2c786c;
}

#ifndef BONUS

void	parse_properties(t_parser *this)
{
	if (this == NULL || this->tokens.arr == NULL)
	{
		put_error(g_game, ft_strdup("empty file!"));
	}
	else
	{
		parse_resultion(this, get_token_by_key(this, "R"));
		parse_sprite(this, get_token_by_key(this, "S"), 2);
		parse_ceil(this, get_token_by_key(this, "C"));
		parse_floor(this, get_token_by_key(this, "F"));
		parse_no_tex(this, get_token_by_key(this, "NO"));
		parse_we_tex(this, get_token_by_key(this, "WE"));
		parse_ea_tex(this, get_token_by_key(this, "EA"));
		parse_so_tex(this, get_token_by_key(this, "SO"));
	}
}

#else

void	parse_properties(t_parser *this)
{
	if (this == NULL || this->tokens.arr == NULL)
	{
		put_error(g_game, ft_strdup("empty file!"));
	}
	else
	{
		parse_resultion(this, get_token_by_key(this, "R"));
		parse_sprite_bonus(this);
		parse_ceil(this, get_token_by_key(this, "C"));
		parse_floor(this, get_token_by_key(this, "F"));
		parse_no_tex(this, get_token_by_key(this, "NO"));
		parse_we_tex(this, get_token_by_key(this, "WE"));
		parse_ea_tex(this, get_token_by_key(this, "EA"));
		parse_so_tex(this, get_token_by_key(this, "SO"));
	}
}

#endif

void	parser_do_final(t_parser *this)
{
	g_game = this->g;
	this->get_lines(this);
	this->parse_file(this);
	init_tex();
	parse_properties(this);
	parse_map(this);
	this->tokens.free(&this->tokens, &free_token);
	if (g_game->player.render == NULL)
		put_error(g_game, ft_strdup("no player"));
}
