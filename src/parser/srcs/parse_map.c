/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:44:07 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:44:09 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_game *game;

void    get_walls(t_parser *this)
{
	t_vector real_pos;
	char *l;

	new_vector(&real_pos, 0 , 0);
	while (real_pos.y < this->lines.index)
	{
		real_pos.x = 0;
		l = (char *) this->lines.get(&this->lines , (int) real_pos.y);
		push_n_walls(this, l, real_pos);
		push_s_walls(this, l ,real_pos);
		real_pos.y += 1.0;
	}
	real_pos.x = 0;
	real_pos.y = 0;
	while (real_pos.x < game->bi)
	{
		push_e_walls(real_pos);
		if(real_pos.x > 0)
			push_w_walls(real_pos);
		real_pos.x += 1;
	}
}


void  create_map_p(t_parser *this)
{
	size_t i ;
	char *line;
	int len;

	game = this->g;  
	game->hvalue =64;
	game->wvalue = 64;
	game->bi = 0;
	i = 0;
	while (i < this->lines.index)
	{
		line = this->lines.get(&(this->lines),i);
		len = ft_strlen(line);
		if(len > game->bi)
			game->bi = len;
		i++;
	}
	get_walls(this);
	get_sprites(this);

}

void copy_to_values(void *item)
{
	char *line = (char *) item;
	if (line != NULL)
		game->parser->lines.push(&game->parser->lines, ft_strdup(line), sizeof(char *));
}


void parse_map(t_parser *this)
{
	t_token *token;

	token = get_token_by_key(this ,"MAP");
	if(token == NULL)
		put_error(this->g, ft_strdup("no map"));
	else
	{
		this->lines.free(&this->lines, &free);
		new_array_list(&this->lines, token->values.index, sizeof(char *));
		token->values.foreach(&token->values, &copy_to_values);
		create_map_p(this);

	}
}
