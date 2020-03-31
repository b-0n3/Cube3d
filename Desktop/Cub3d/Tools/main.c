
#include "Cube3d.h"

void line(void *mlx , void *window ,t_vector *pos, t_vector *dir)
{
   // if (pos->x < dir->x)
    //    ft_swap(&pos, &dir);    
     int m_new = 2 * (dir->y - pos->y); 
     int slope_error_new = m_new - (dir->x - pos->x); 
     int x = pos->x;
     int y = pos->y;

    while ( x <= dir->x) 
    { 
         mlx_pixel_put(mlx , window, (int) x ,(int) y, 0xFFFFFF);
      slope_error_new += m_new; 
       if (slope_error_new >= 0) 
       { 
          y++; 
          slope_error_new  -= 2 * (dir->x - pos->x); 
       } 
       x++;
   } 

//   while (y1 < y2)
//   {
//     int x1 = x;
//   while ( x1 < x2)
//   { 
   
//       mlx_pixel_put(mlx ,window , x1, y1 , 255);
//     x1++;
     
//   }
//   y1++;
//   }
   // ft_swap(&pos, &dir);  
}
t_game *g;
void drawwall(void *ir)
{
    t_wall *wall = (t_wall *) ir;
    if(wall != NULL)
    {
        line(g->window.mlx, g->window.win ,wall->pos , wall->dir);
    }



}
void draw_rec(void *mlx , void *window , int x,int y1 , int x2, int y2)
{
  while (y1 < y2)
  {
    int x1 = x;
  while ( x1 < x2)
  { 
   
      mlx_pixel_put(mlx ,window , x1, y1 , 500);
    x1++;
     
  }
  y1++;
  }

}

void drawmap(t_game *game)
{
    for(int y = 0 ; y < game->parser->lines.index; y++)
    {
        char *line = game->parser->lines.get(&(game->parser->lines),y);
        for (int x = 0; x < ft_strlen(line); x++)
        {
            if (line[x] == '1')
            {
            draw_rec(game->window.mlx, game->window.win ,
                x * game->wvalue , y * game->hvalue ,
                (x + 1) * game->wvalue , (y + 1) * game->hvalue);
            }
        }
    }
}

void startgame( t_game *game)
{
    g = game;
    

    //drawmap(game);
    game->walls.foreach(&(game->walls), &drawwall);
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