#include "Cube3d.h"
#include "key_linux.h"

extern t_game *game;

int  key_pressed(int k_code , void *ptr)
{
    if(k_code == UP_ARROW)
    {
        game->player.w_dir = 1;
    }
    else if (k_code == DOWN_ARROW)
    {
    game->player.w_dir =-1;
    }
    else if (k_code == LEFT_ARROW)
    {
        game->player.t_dir = -1;
    }
    else if (k_code == RIGHT_ARROW)
    {
        game->player.t_dir = 1;
    }
     if (k_code == EXIT_KEY)
    {
        game->exit(game, NULL);
    }
    return 0;
}

int key_relased(int k_code , void *ptr)
{
    if(k_code == UP_ARROW)
    {
        game->player.w_dir = 0;
    }
    else if (k_code == DOWN_ARROW)
    {
        game->player.w_dir = 0;
    }
    else if (k_code == LEFT_ARROW)
    {
        game->player.t_dir = 0;
    }
    else if (k_code == RIGHT_ARROW)
    {
        game->player.t_dir = 0;
    }

    return 0;
}