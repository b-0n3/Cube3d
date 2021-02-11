/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:52:50 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:52:53 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

#define FRAME_CAP 12000.0
long  SECOND  =1000000000L;
long long  lastTime;
double   frame_time = 1.0 / FRAME_CAP;
double  unprocessed = 0;
t_game  *g;

void    render()
{
	g->player.render(&(g->player));
	g->window.img->show(g->window);
}



int update(int key)
{
	t_bool rend;
	long long  start_time; 
	long long passed_time;

	start_time  = get_current_time();
	passed_time = start_time - lastTime;
	(void)key;
	rend = FALSE;
	lastTime = start_time;
	unprocessed += (passed_time / (double) SECOND);
	while (unprocessed > frame_time)
	{
		rend = TRUE;
		unprocessed -= frame_time;
		g->player.update(&g->player);
	}
	if(rend == 1)
	{
		g->window.img->clear(g->window);
		render();
	}
	return 0;
}


void startgame(t_game *game)
{
	g = game;


	g->window.win =  mlx_new_window(g->window.mlx, 
			(int) g->width, (int) g->heigth , "CUB3d");
	mlx_hook( g->window.win, 5,(1L<<3), mouse_relased, (void*)0);
	mlx_mouse_hook (g->window.win, mouse_pressed, (void*) 0 );
	mlx_hook(g->window.win ,2,(1L << 0),key_pressed ,(void *) 0);
	mlx_hook(g->window.win , 3,(2L << 0), key_relased , (void *) 0);
	mlx_loop_hook(g->window.mlx, update, (void *) 0);
	mlx_loop(game->window.mlx);
}



int main(int argc , char **paths)
{
	t_game game;

	if (argc  >=2)
	{
		
		new_game(&game, paths[1]);
		lastTime = get_current_time();
		if (argc == 3)
		{
		
			game.player.render(&(game.player));
			game.save(&game);
		}
		else
			startgame(&game);
	}else
		perror("invalid call");
	return 0;
}
