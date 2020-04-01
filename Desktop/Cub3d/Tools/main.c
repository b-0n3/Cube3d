
#include "Cube3d.h"




void drawmap(t_game *game)
{
    t_vector *pos = new_vector_pointer(0,0);
    for(int y = 0 ; y < game->parser->lines.index; y++)
    {
        char *line = game->parser->lines.get(&(game->parser->lines),y);
        for (int x = 0; x < ft_strlen(line); x++)
        {
            
            if (line[x] == '1')
            {
                pos->x = x *game->wvalue;
                pos->y = y * game->hvalue;
            draw_rec(game->window ,*pos,(int) game->hvalue - 3 ,0xeb4d55);
            }
        }
    }
}

void startgame( t_game *game)
{
    
    

    drawmap(game);
   // game->walls.foreach(&(game->walls), &drawwall);
   game->player.render(&(game->player));
    mlx_loop(game->window.mlx);
}

void printVer(void *item)
{
    printf("%s\n", (char *) item);
}

int main(void)
{
    
    t_game game;

    new_game(&game, "/home/b0n3/Desktop/Cube3d/Desktop/Cub3d/map.cub");

    startgame(&game);

    // t_parser tp;
    // new_parser(&tp);
    // tp.get_lines(&tp, "map.cub");
    
    //     char *line;
    //     while ((line = tp.lines.pull(&(tp.lines)) )!= NULL)
    //     {
    //             printVer((void *) line);
    //             free( line);
    //     }
        
    // tp.lines.free(&(tp.lines), NULL);
    return 0;
}