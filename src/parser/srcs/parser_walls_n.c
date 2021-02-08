#include "cub3d.h"

extern t_game *game;

double push_n_walls_c(char *arr, t_vector r_p, char *l ,char *l_d)
{
    while (ft_strchr(arr,l[(int) r_p.x]) != NULL
                 &&ft_strchr(arr,l_d[(int) r_p.x])   == NULL)
                {
                    if ( l[(int) r_p.x] == '\0' || l_d[(int)r_p.x] == '\0')
                        break;
                    r_p.x += 1;
                }
    return r_p.x;
}
void push_n_wall(t_vector start ,t_vector r_p)
{
     if (start.x < r_p.x)
                    game->walls.push(&(game->walls),
                    new_wall(
                        new_vector_pointer(start.x * game->wvalue, (start.y + 1)
                        *game->hvalue),
                        new_vector_pointer((r_p.x )* game->wvalue ,(r_p.y + 1)
                   *game->hvalue), 0), sizeof(t_wall));
}
void push_player(char *l, t_vector r_p)
{
    char *arr;

    arr = "NSEW";
     if(ft_strchr(arr, l[(int)r_p.x]) !=  NULL && l[(int) r_p.x] != '\0')
    {
                    if (game->player.free != NULL)
                        put_error(game , ft_strjoin("diplicate player pos at line\n",l));
                else{
                  new_player(&(game->player), 
                  new_vector_pointer(r_p.x *game->wvalue +
                   (0.5 * game->wvalue ), r_p.y *
                    game->hvalue + (0.5 *game->hvalue)) ,
                    l[(int)r_p.x]);
                    l[(int) r_p.x] = '0';
                }
    }
}
void push_n_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_d;
    t_vector start;
    char *arr;

    #ifdef BONUS

    arr =  "1s2";
    #else

    arr = "1s";
    #endif

    game = this->g;
    new_vector(&start , r_p.x , r_p.y);
    l_d = this->lines.get(&(this->lines),r_p.y + 1);
    if (l_d != NULL)
     while (l[(int)r_p.x] != '\0' && l_d[(int) r_p.x] != '\0' )
     {
         
             r_p.x = push_n_walls_c(arr ,r_p, l ,l_d);
                push_n_wall(start , r_p);
                push_player(l, r_p);
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;    
    }
}