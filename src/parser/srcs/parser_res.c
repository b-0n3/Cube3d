/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:01 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:46:03 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_bool is_all_digit(char *arr)
{
	size_t i;

	i = 0;
	if (arr == NULL)
		return (FALSE);
	while (ft_iswhitespace(arr[i]))
		i++;
	while(ft_isdigit(arr[i]))
		i++;
	if (i != ft_strlen(arr))
		return (FALSE);
	return TRUE;
}

t_bool check_res_line(t_array_list lines)
{
	char *l[2];
	if (lines.arr == NULL || lines.index != 2)
		return (FALSE);
	l[0] = lines.get(&lines,0);
	l[1] = lines.get(&lines,1);
	if (l[0] ==NULL || l[1] == NULL)
		return (FALSE);


	return (is_all_digit(l[0]) && is_all_digit(l[1]));
}
void init_window(t_game *g, int h, int w)
{
	g->heigth = (h > 1440 || h <= 0) ? 1440 : h;
	g->width = (w > 2560 || w <= 0) ? 2560 : w;
	g->window.mlx = mlx_init();
	g->window.img = (t_image *) malloc (sizeof(t_image));
	init_image(g->window.img, g->window);

}
void parse_resultion(t_parser *this , t_token *token)
{
	t_array_list word;
	char *line;
	int h;
	int w;
	if (this != NULL  && token != NULL && token->values.arr != NULL)
	{
		h = 0;
		w = 0;
		line = token->values.pull(&(token->values));
		new_array_list(&word,2,sizeof(char *));
		split_that(&word, line, ' ');
		if (check_res_line(word))
		{
			h = ft_atoi((char*)word.get(&word, 1));
			w = ft_atoi((char *) word.get(&word, 0));
		}
		else 
			put_error(this->g , ft_strdup("invalid resulotion"));
		init_window(this->g, h, w);
		word.free(&word , &free);
	}
	else
		put_error(this->g , ft_strdup("no resulotion"));
}
