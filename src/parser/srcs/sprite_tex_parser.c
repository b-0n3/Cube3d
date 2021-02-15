/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tex_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:53:04 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:53:06 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
***  @autor : b0n3
*** X |Y   Z   | ....
*** x : how many texture in the line
*** Y : a number defines the kind  of  the texture
*** Z : the full path to the image
*/
extern t_game *g_game;

void	parse_b_sprite(void *item)
{
	char			*line;
	t_token			*token;
	t_array_list	*list;
	int				kind;

	line = (char *)item;
	if (item != NULL)
	{
		token = (t_token *)malloc(sizeof(t_token));
		list = ft_split_property(line);
		new_token(token, *list);
		kind = ft_atoi(token->token);
		parse_sprite(g_game->parser, token, kind);
		list->free(list, &free);
		free(list);
		token->free(token);
	}
	else
		put_error(g_game, ft_strdup("invalid sp1 texture"));
}

void	sprite_tex_parser(char *line)
{
	t_array_list	data;
	char			*l;
	int				nb;

	new_array_list(&data, 3, sizeof(char *));
	split_that(&data, line, '|');
	if (data.index == 0)
		put_error(g_game, ft_strdup("invalid line"));
	else
	{
		l = data.pull(&data);
		nb = ft_atoi(l);
		free(l);
		if (nb > 0)
		{
			data.foreach(&data, &parse_b_sprite);
		}
		else
			put_error(g_game, ft_strdup("invalid sp2 texture"));
	}
	data.free(&data, &free);
}
