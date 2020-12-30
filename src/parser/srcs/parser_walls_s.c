#include "parser.h"
t_game *game;

void push_s_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_u;
    t_vector start;

    l_u = this->lines.get(&(this->lines),r_p.y - 1);
    game = this->g_p;
    new_vector(&start , r_p.x , r_p.y);
    if (l_u != NULL)
      while (l[(int)r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
     {
                while ((l[(int) r_p.x] == '1' ||l[(int) r_p.x] == 's'||
                l[(int) r_p.x] == '2' ) && l_u[(int)r_p.x] !='1'
                 && l[(int) r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
                    r_p.x += 1;
                if (start.x < r_p.x)
                        insert_s_wall(start.x,start.y,r_p.x,r_p.y);
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;
                
    }
}

void insert_s_wall(double s_x, double s_y, double e_x, double e_y){
    game->walls.push(&(game->walls),
    new_wall(
        new_vector_pointer(s_x * game->wvalue, 
                            (s_y  ) * game->hvalue),
        new_vector_pointer((e_x )* game->wvalue ,
                        (e_y )*game->hvalue),0),
                        sizeof(t_wall));
}