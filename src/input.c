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

# include "cub3d.h"
# include "key_macos.h"

extern	t_game	*game;

int key_pressed_c(int k_code)
{
	if (k_code == K_W)
		game->player.w_dir = 1;
	if (k_code == K_S)
		game->player.w_dir = -1;
	if (k_code ==K_D)
	{
		game->player.w_dir =game->player.w_dir == 0? 1 : game->player.w_dir;
		game->player.side_angle = 90 * M_PI /180;
	}
	else if (k_code == K_A)
	{
		game->player.w_dir =game->player.w_dir == 0? 1 : game->player.w_dir;
		game->player.side_angle = -90 * M_PI /180;
	}
	return (0);
}
int		key_pressed(int k_code, void *ptr)
{
	ptr = NULL;
	if (k_code == K_AR_D)
		game->player.offset = -80;
	if (k_code == K_AR_U)
		game->player.offset = 80;
	if (k_code == K_AR_L)
		game->player.t_dir = -1;
	if (k_code == K_AR_R)
		game->player.t_dir = 1;
	if (k_code == K_ESC)
		game->exit(game, NULL);

	return key_pressed_c(k_code);
}

int mouse_relased(int button, int x, int y, void *param)
{
	game->player.t_dir = 0;
	return 0;
}

int mouse_pressed(int button, int x, int y, void *param)
{


	if ((x >= game->width /2))
		game->player.t_dir = 1;
	else if ((x <= game->width / 2) && x > 0)
		game->player.t_dir = -1;
	else
		game->player.t_dir = 0;
	return (1);
}

int key_released_c(int k_code )
{
	if (k_code == K_D)
	{
		game->player.w_dir = 0;
		game->player.side_angle = 0;
	}
	if (k_code == K_A)
	{
		game->player.w_dir = 0;
		game->player.side_angle = 0;
	}
	if (k_code == K_COMAND)
	{
		game->player.w_dir = 0;
		game->player.side_angle = 0;
		game->player.t_dir = 0;
	}
	return (0);
}

int		key_relased(int k_code, void *ptr)
{
	ptr = NULL;
	if (k_code == K_AR_U)
		game->player.offset = 0;
	if (k_code == K_AR_D)
		game->player.offset = 0;
	if (k_code == K_AR_L)
		game->player.t_dir = 0;
	if (k_code == K_AR_R)
		game->player.t_dir = 0;
	if (k_code == K_W)
		game->player.w_dir = 0;
	if (k_code == K_S)
		game->player.w_dir = 0;
	return key_released_c(k_code);
}
