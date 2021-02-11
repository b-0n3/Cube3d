/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:17:35 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:39:37 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_game(t_game *this, char *file_name)
{
	this->parser = (t_parser *)malloc(sizeof(t_parser));
	this->heigth = 0.0f;
	this->wvalue = 0.0f;
	this->bi = 0;
	new_array_list(&(this->errors), 10, sizeof(char *));
	new_array_list(&(this->walls), 10, sizeof(t_wall));
	new_array_list(&(this->sprites), 10, sizeof(t_sprites));
	new_array_list(&(this->lights), 10, sizeof(t_sprites));
	new_array_list(&this->allocated_sp_tex, 2, sizeof(t_sp_texture));
	new_array_list(&this->allocated_tex, 4, sizeof(t_texture));
	new_parser(this->parser, file_name, this);
	this->exit = &__exit_;
	this->save = &save_game;
	this->free = &free_game;
	this->parser->do_final(this->parser);
	if (this->errors.index > 0)
		this->exit(this, NULL);
}
