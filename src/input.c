# include "cub3d.h"
# include "key_macos.h"

extern	t_game	*game;
int		key_pressed(int k_code, void *ptr)
{
	ptr = NULL;
	if (k_code == K_AR_D)
		game->player.offset = -80;
	else if (k_code == K_AR_U)
		game->player.offset = 80;
	else if (k_code == K_AR_L)
		game->player.t_dir = -1;
	else if (k_code == K_AR_R)
		game->player.t_dir = 1;
	if (k_code == K_ESC)
		game->exit(game, NULL);
	else if (k_code == K_W)
		game->player.w_dir = 1;
	else if (k_code == K_S)
		game->player.w_dir = -1;
	else if (k_code ==K_D)
		game->player.t_dir = 1;
	else if (k_code == K_A)
		game->player.t_dir = -1;
	
	return 0;
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

int		key_relased(int k_code, void *ptr)
{
	ptr = NULL;
	if (k_code == K_AR_U)
		game->player.offset = 0;
	else if (k_code == K_AR_U)
		game->player.offset = 0;
	else if (k_code == K_AR_L)
		game->player.t_dir = 0;
	else if (k_code == K_AR_R)
		game->player.t_dir = 0;
	else if (k_code == K_W)
		game->player.w_dir = 0;
	else if (k_code == K_S)
		game->player.w_dir = 0;
	else if (k_code == K_D)
		game->player.t_dir = 0;
	else if (k_code == K_A)
		game->player.t_dir = 0;
	return (0);
}