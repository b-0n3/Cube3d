
#include "Cube3d.h"
#include <sys/time.h>
#define FRAME_CAP 50000.0
long  SECOND  =1000000000L;

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

void drawborder(t_game *game)
{
    t_vector *pos = new_vector_pointer(0,0);
    for(int y = 0 ; y < game->parser->lines.index; y++)
    {
        char *line = game->parser->lines.get(&(game->parser->lines),y);
        for (int x = 0; x < ft_strlen(line); x++)
        {
            
                pos->x = x *game->wvalue;
                pos->y = y * game->hvalue;
            draw_rec(game->window ,*pos,(int) game->hvalue - 3 ,0xfaf5e4);
            
        }
    }
}
t_game  *g;

long long  get_current_time()
{
    struct timeval cur;
    gettimeofday(&cur, NULL);
    long long nano = (long long )cur.tv_sec*1000000 + (long long )cur.tv_usec;
    return nano;
}

void    render()
{
     drawborder(g);
        drawmap(g);
     g->player.render(&(g->player));
    g->window.img->show(g->window);
}

long long  lastTime;
double   frame_time = 1.0 / 5000.0;
double  unprocessed = 0;

int update(int key)
{
    t_bool rend = FALSE;
    (void)key;
   // mlx_clear_window(g->window.mlx, g->window.win);
    //t_game *gg = g;
    long long  start_time = get_current_time();
    long long passed_time = start_time - lastTime;
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
    else
    {
        system("sleep 0.001");

    }
   // printf("fdsfsdf sd fsdf %d", rend);
    
    
    return 0;
}


void startgame( t_game *game)
{
    
    
   //drawborder(game);
   // drawmap(game);
    g = game;
    //mlx_do_key_autorepeatoff(g->window.mlx);
    

    mlx_hook(g->window.win ,2,(1L << 0),key_pressed ,(void *) 0);
    mlx_hook(g->window.win , 3,(2L << 0)  , key_relased , (void *) 0);
     mlx_loop_hook(g->window.mlx, update, (void *) 0);
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
    lastTime = get_current_time();
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