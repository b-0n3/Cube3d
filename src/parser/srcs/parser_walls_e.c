#include "cub3d.h"

extern t_game *game;

double push_e_walls_c(char *arr ,t_vector p, char *l )
{
    int len;

     while (ft_strchr(arr,l[(int) p.x]) != NULL)
        {
            p.y += 1;
            l = game->parser->lines.get(&game->parser->lines, p.y);
            if (l == NULL)
                break;
            len = ft_strlen(l);
            if(p.x >= len)
             break;
        }
        return p.y;
}
void push_e_wall(t_vector start , t_vector p)
{
    if (start.y < p.y)
                  game->walls.push(&(game->walls),
                   new_wall(
                       new_vector_pointer((start.x +1 ) * game->wvalue,
                        (start.y )*game->hvalue),
                        new_vector_pointer((p.x + 1)* game->wvalue ,
                        (p.y )*game->hvalue),3), sizeof(t_wall));
}

void push_e_walls(t_vector p)
{
    char *l;
    t_vector start;
    char *arr;

    #ifdef BONUS

    arr =  "1s2";
    #else

    arr = "1s";
    #endif

    new_vector(&start , p.x, p.y);
    l = game->parser->lines.get(&game->parser->lines, p.y);
    while (l != NULL && p.y < game->parser->lines.index)
    {
         l = game->parser->lines.get(&game->parser->lines, p.y);
            p.y = push_e_walls_c(arr, p,l);
            push_e_wall(start , p);
                 p.y += 1;
                 start.x = p.x;
                 start.y = p.y;
    }
}