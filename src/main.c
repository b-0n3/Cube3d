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
#define FRAME_CAP 13000.0

const long		g_second = 1000000000L;
t_long			g_last_time;
const double	g_frame_time = 1.0 / FRAME_CAP;
double			g_unprocessed;
t_game			*g_game;

void	render(void)
{
	g_game->player.render(&(g_game->player));
	g_game->window.img->show(g_game->window);
}

int		update(int key)
{
	t_bool	rend;
	t_long	start_time;
	t_long	passed_time;

	start_time = get_current_time();
	passed_time = start_time - g_last_time;
	(void)key;
	rend = FALSE;
	g_last_time = start_time;
	g_unprocessed += (passed_time / (double)g_second);
	while (g_unprocessed > g_frame_time)
	{
		rend = TRUE;
		g_unprocessed -= g_frame_time;
		g_game->player.update(&g_game->player);
	}
	if (rend == 1)
	{
		g_game->window.img->clear(g_game->window);
		render();
	}
	return (0);
}

void	print_usage(void)
{
	const char	*error = "cub3D: illegal options\n";
	char		*usage;

	usage = "usage: cub3D <filename:.cub>\n\tcub3D <filename:.cub> --save";
	write(1, error, ft_strlen(error));
	write(1, usage, ft_strlen(usage));
	exit(1);
}

void	startgame(t_game *game)
{
	g_game = game;
	g_game->window.win = mlx_new_window(g_game->window.mlx,
			(int)g_game->width, (int)g_game->heigth, "CUB3d");
	mlx_hook(g_game->window.win, 5, (1L << 3), mouse_relased, (void*)0);
	mlx_mouse_hook(g_game->window.win, mouse_pressed, (void*)0);
	mlx_hook(g_game->window.win, 2, 0, key_pressed, (void *)0);
	mlx_hook(g_game->window.win, 3, 0, key_relased, (void *)0);
	mlx_loop_hook(g_game->window.mlx, update, (void *)0);
	mlx_loop(g_game->window.mlx);
}

int		main(int argc, char **paths)
{
	t_game game;

	if (argc < 2 || argc > 3)
		print_usage();
	if (argc == 3 && ft_strncmp(paths[2], "--save", ft_strlen("--save")))
		print_usage();
	if (!ft_check_file(paths[1], ".cub"))
		print_usage();
	new_game(&game, paths[1]);
	g_last_time = get_current_time();
	if (argc == 3)
	{
		game.player.render(&(game.player));
		game.save(&game);
	}
	else
		startgame(&game);
	return (0);
}
