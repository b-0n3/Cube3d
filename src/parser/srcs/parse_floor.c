/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:43:53 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:43:57 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	parse_floor(t_parser *this, t_token *token)
{
	parse_floor_tex(this->g, token);
}

#else

void	parse_floor(t_parser *this, t_token *token)
{
	parse_floor_color(this->g, token);
}

#endif

void	parse_floor_color(t_game *this, t_token *token)
{
	t_array_list	word;
	char			*line;
	int				color;

	if (this != NULL && token != NULL)
	{
		new_array_list(&word, 2, sizeof(char *));
		line = token->values.get(&(token->values), 0);
		if (line == NULL)
			put_error(this, ft_strdup("invalid floor color"));
		split_that(&word, line, ',');
		color = parse_color(this, word);
		if (color < 0)
			put_error(this, ft_strdup("invalid floor color"));
		else
			this->color[4] = color;
		free(word.arr);
	}
}

void	parse_floor_tex(t_game *this, t_token *token)
{
	char *filename;

	if (this == NULL || token == NULL)
		return ;
	filename = (char *)token->values.pull(&(token->values));
	if (!ft_check_file(filename, ".xpm"))
		put_error(this, ft_strdup("invalid floor texture file"));
	else
		this->floor = new_sp_texture(filename, 10);
	free(filename);
}
