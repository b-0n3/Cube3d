#include "cub3d.h"
t_game *game;
double push_s_walls_c(char *arr , char *l, char *l_u ,t_vector r_p)
{
   while (ft_strchr(arr,l[(int) r_p.x]) != NULL  &&
                ft_strchr(arr, l_u[(int) r_p.x]) == NULL)
                    r_p.x += 1;
    return r_p.x;
}
void push_s_wall(t_vector start , t_vector r_p)
{
      if (start.x < r_p.x)
                {
                   game->walls.push(&(game->walls),
                   new_wall(
                     new_vector_pointer(start.x * game->wvalue, (start.y )*game->hvalue),
                   new_vector_pointer((r_p.x )* game->wvalue ,(r_p.y )*game->hvalue),2),
                    sizeof(t_wall));
                }
}

void push_s_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_u;
    t_vector start;
    char *arr;

    l_u = this->lines.get(&(this->lines),r_p.y - 1);
    #ifdef BONUS

    arr =  "1s2";
    #else

    arr = "1s";
    #endif
    game = this->g;
    new_vector(&start , r_p.x , r_p.y);
    if (l_u != NULL)
      while (l[(int)r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
     {

            r_p.x = push_s_walls_c(arr , l , l_u , r_p);
            push_s_wall(start ,r_p);
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;
                
    }
}