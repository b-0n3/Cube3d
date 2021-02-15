/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:52:41 by aait-ham          #+#    #+#             */
/*   Updated: 2021/02/09 19:52:43 by aait-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_macos.h"

extern	t_game	*g_game;

int		key_pressed_c(int k_code)
{
	if (k_code == K_W)
		g_game->player.w_dir = 1;
	if (k_code == K_S)
		g_game->player.w_dir = -1;
	if (k_code == K_D)
	{
		g_game->player.w_dir = 1;
		g_game->player.side_angle = 90 * M_PI / 180;
	}
	else if (k_code == K_A)
	{
		g_game->player.w_dir = 1;
		g_game->player.side_angle = -90 * M_PI / 180;
	}
	return (0);
}

int		key_pressed(int k_code, void *ptr)
{
	ptr = NULL;
	if (k_code == K_AR_D)
		g_game->player.offset = -80;
	if (k_code == K_AR_U)
		g_game->player.offset = 80;
	if (k_code == K_AR_L)
		g_game->player.t_dir = -1;
	if (k_code == K_AR_R)
		g_game->player.t_dir = 1;
	if (k_code == K_ESC)
		g_game->exit(g_game, NULL);
	return (key_pressed_c(k_code));
}

int		key_released_c(int k_code)
{
	if (k_code == K_D)
	{
		g_game->player.w_dir = 0;
		g_game->player.side_angle = 0;
	}
	if (k_code == K_A)
	{
		g_game->player.w_dir = 0;
		g_game->player.side_angle = 0;
	}
	if (k_code == K_COMAND)
	{
		g_game->player.w_dir = 0;
		g_game->player.side_angle = 0;
		g_game->player.t_dir = 0;
	}
	return (0);
}

int		key_relased(int k_code, void *ptr)
{
	ptr = NULL;
	if (k_code == K_AR_U)
		g_game->player.offset = 0;
	if (k_code == K_AR_D)
		g_game->player.offset = 0;
	if (k_code == K_AR_L)
		g_game->player.t_dir = 0;
	if (k_code == K_AR_R)
		g_game->player.t_dir = 0;
	if (k_code == K_W)
		g_game->player.w_dir = 0;
	if (k_code == K_S)
		g_game->player.w_dir = 0;
	return (key_released_c(k_code));
}
