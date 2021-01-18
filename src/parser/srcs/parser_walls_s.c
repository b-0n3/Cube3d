#include "cub3d.h"
t_game *game;

// void push_s_walls(t_parser *this,char *l ,t_vector r_p)
// {
//     char *l_u;
//     t_vector start;

//     l_u = this->lines.get(&(this->lines),r_p.y - 1);
//     game = this->g;
//     new_vector(&start , r_p.x , r_p.y);
//     if (l_u != NULL)
//       while (l[(int)r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
//      {
//         printf(" x %.2f, y %.2f \n line1  %s \nchar %c \n line2  %s \nchar %c \n ", r_p.x, r_p.y, l, l[(int)r_p.x] , l_u , l_u[(int )r_p.x]);
//                 while ((l[(int) r_p.x] == '1' ||l[(int) r_p.x] == 's'||
//                 l[(int) r_p.x] == '2' ) && l_u[(int)r_p.x] !='1'
//                  && l[(int) r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
//                     r_p.x += 1;
//                 if (start.x < r_p.x)
//                         insert_s_wall(start.x,start.y,r_p.x,r_p.y);
//                  r_p.x += 1;
//                  start.x = r_p.x;
//                  start.y = r_p.y;
                
//     }
// }

// void insert_s_wall(double s_x, double s_y, double e_x, double e_y){
//     game->walls.push(&(game->walls),
//     new_wall(
//         new_vector_pointer(s_x * game->wvalue, 
//                             (s_y  ) * game->hvalue),
//         new_vector_pointer((e_x )* game->wvalue ,
//                         (e_y )*game->hvalue),0),
//                         sizeof(t_wall));
// }
void push_s_walls(t_parser *this,char *l ,t_vector r_p)
{
    char *l_u = this->lines.get(&(this->lines),r_p.y - 1);
    t_vector start;
    char *arr;

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
                while (ft_strchr(arr,l[(int) r_p.x]) != NULL && l_u[(int)r_p.x] !='1' && l[(int) r_p.x] != '\0' && l_u[(int)r_p.x] != '\0')
                    r_p.x += 1;
                if (start.x < r_p.x)
                {
                   int xx= game->walls.push(&(game->walls),new_wall(new_vector_pointer(start.x * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((r_p.x )* game->wvalue ,(r_p.y )*game->hvalue),2), sizeof(t_wall));
                 //   printf("this is xx %d",xx);
                }
                 r_p.x += 1;
                 start.x = r_p.x;
                 start.y = r_p.y;
                
    }
}