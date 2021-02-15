/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:26:01 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/15 15:26:03 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_macos.h"

extern t_game *g_game;

int		mouse_relased(int button, int x, int y, void *param)
{
	x = 1;
	y = 0;
	param = NULL;
	button = 1;
	g_game->player.t_dir = 0;
	return (0);
}

int		mouse_pressed(int button, int x, int y, void *param)
{
	y = 0;
	button = 0;
	param = NULL;
	if ((x >= g_game->width / 2))
		g_game->player.t_dir = 1;
	else if ((x <= g_game->width / 2) && x > 0)
		g_game->player.t_dir = -1;
	else
		g_game->player.t_dir = 0;
	return (1);
}
