/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ceilling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:45:21 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:45:23 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_ceil(t_parser *this, t_token *token)
{
	parse_ceilling_color(this->g ,token);
}

int parse_color(t_game *g, t_array_list rgb_colors)
{
	int val[3];
	int i;
	char *v;

	i = 0;
	while(i < 3)
		val[i++] = -1;
	if(rgb_colors.index != 3)
		return -1;
	i = 0;
	while((v = (char *) rgb_colors.pull(&rgb_colors)) != NULL)
	{
		val[i++] = ft_atoi(v);
		if (val[i - 1]  > 255 || val[i - 1] < 0)
			put_error(g, ft_strjoin("invalid  color\n", v));
		free(v);
	}
	return list_rgb_to_int(val);
}

int list_rgb_to_int(int *val)
{
	int i;

	i = 0;
	while(i < 3)
	{
		if(val[i++] == -1)
			return -1;
	}
	return rgb_to_int(val[0],val[1],val[2]);
}

void parse_ceilling_color(t_game *this, t_token *token)
{
	t_array_list  word;
	char          *line;
	int           color;


	if (this != NULL && token != NULL)
	{
		new_array_list(&word,2,sizeof(char *));
		line = token->values.get(&(token->values),0);
		if(line == NULL)
			put_error(this,ft_strdup("invalid ceilling color"));
		split_that(&word, line, ',');
		color = parse_color(this , word);
		if (color < 0)
			put_error(this,ft_strdup("invalid ceilling color"));
		else
			this->color[5] = color;
	}
}
