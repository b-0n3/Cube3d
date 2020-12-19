
#include "Cube3d.h"
#include <sys/time.h>
#define FRAME_CAP 20000.0
long  SECOND  =1000000000L;
long long  lastTime;
double   frame_time = 1.0 / FRAME_CAP;
double  unprocessed = 0;
t_game  *g;

void drawmap(t_game *game)
{
   t_vector pos;
     new_vector(&pos, 0,0);
    for(int y = 0 ; y < game->parser->lines.index; y++)
    {
        char *line = game->parser->lines.get(&(game->parser->lines),y);
        for (int x = 0; x < ft_strlen(line); x++)
        {
            
            if (line[x] == '1')
            {
                pos.x = x * (game->wvalue  );
                pos.y = y * (game->hvalue);
            draw_rec(game->window ,pos, (int) (game->hvalue - 3 ),0xeb4d55);
            }
        }
    }
}

void drawborder(t_game *game)
{
    t_vector pos;

     new_vector(&pos, 0,0);
    for(int y = 0 ; y < game->parser->lines.index; y++)
    {
        char *line = game->parser->lines.get(&(game->parser->lines),y);
        for (int x = 0; x < ft_strlen(line); x++)
        {
                pos.x = x * (game->wvalue);
                pos.y = y * (game->hvalue);
            draw_rec(game->window ,pos,(int) (game->hvalue - 3 ),0xfaf5e4);
            
        }
    }
}


long long  get_current_time()
{
    struct timeval cur;

    gettimeofday(&cur, NULL);
    return ((long long ) cur.tv_sec * 1000000 + (long long ) cur.tv_usec); 
}


void    render()
{
    g->player.render(&(g->player));
    g->window.img->show(g->window);
}



int update(int key)
{
    t_bool rend = FALSE;
    long long  start_time; 
    long long passed_time;
    start_time  = get_current_time();
    passed_time = start_time - lastTime;
    (void)key;
    
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
        system("sleep 0.01");

    }
    
    
    return 0;
}


void startgame(t_game *game)
{
    g = game; 
    mlx_hook( g->window.win, 5,(1L<<3), mouse_relased, (void*)0);


    mlx_mouse_hook (g->window.win, mouse_pressed, (void*) 0 );
    
    mlx_hook(g->window.win ,2,(1L << 0),key_pressed ,(void *) 0);
    mlx_hook(g->window.win , 3,(2L << 0), key_relased , (void *) 0);
     mlx_loop_hook(g->window.mlx, update, (void *) 0);
    
    mlx_loop(game->window.mlx);
}



int main(int argc , char **paths)
{
    t_game gam
    new_game(&game, paths[1]);
    lastTime = get_current_time();
    startgame(&game);
    return 0;
}