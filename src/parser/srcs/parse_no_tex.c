/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_no_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:44:14 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:44:18 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_no_tex(t_parser *this, t_token *token)
{
	char *filename;
	t_texture *tex;

	if (this != NULL)
	{
		if (token == NULL) 
			put_error(this->g , ft_strdup("no no tex"));
		else{
			filename =(char *) token->values.pull(&(token->values));
			if(!ft_check_file(filename, ".xpm"))
				put_error(this->g , ft_strdup("invalid no1 texture"));
			else
			{
				tex = new_texture(filename);
				if(tex == NULL)
					put_error(this->g , ft_strdup("invalid no2 texture"));
				else
				{
					tex->data =  flip_w_arr(tex->data, tex->height * tex->width, tex->width);    
					this->g->n_texture = tex;
				}
			}
		}
	}
}
