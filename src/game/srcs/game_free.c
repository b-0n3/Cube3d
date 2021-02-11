/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:39:12 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:39:15 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_game(void *t)
{
	t_game *this  = (t_game *) t;


	    this->parser->free(this->parser);
	
	   this->player.free(&this->player);
	    this->errors.free(&this->errors ,&free);
	    this->sprites.free(&this->sprites , &free_sprite);
	 this->walls.free(&this->walls, &free_wall);
	
	mlx_clear_window(this->window.mlx, this->window.win);
	mlx_destroy_image(this->window.mlx, this->window.img->img_ptr);
	mlx_destroy_window(this->window.mlx, this->window.win);

}
