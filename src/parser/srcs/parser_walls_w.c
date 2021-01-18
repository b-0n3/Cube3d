#include "cub3d.h"
extern t_game *game;

// void push_w_walls(t_vector p)
// {
// char *l = game->parser->lines.get(&(game->parser->lines), p.y);
//     t_vector start;
//     new_vector(&start , p.x, p.y);
//     int len;
//     while (l != NULL && p.y < game->parser->lines.index)
//     {
//          l = game->parser->lines.get(&game->parser->lines, p.y );
//         while ((l[(int)p.x] == '1' ||l[(int)p.x] == 's'||l[(int)p.x] == '2')&& 
//         l[(int)p.x - 1] != '1' && l[(int)p.x - 1] != '2')
//         {
//             p.y += 1;
//             l = game->parser->lines.get(&game->parser->lines, p.y);
//             if (l != NULL)
//             {
//                 len = ft_strlen(l);
//                 if (p.x >= len)
//                     break;
//             }
//             else 
//                 break;
//         }

//             if (start.y < p.y)
//                 {

//                    game->walls.push(&(game->walls),new_wall(new_vector_pointer((start.x ) * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((p.x)* game->wvalue ,(p.y )*game->hvalue),1), sizeof(t_wall));
//                  //   printf("this is xx %d",xx);
//                 }
//                  p.y += 1;
//                  start.x = p.x;
//                  start.y = p.y;
//     }
// }
void push_w_walls(t_vector p)
{
char *l = game->parser->lines.get(&game->parser->lines, p.y);
    t_vector start;
    new_vector(&start , p.x, p.y);
    int len;
    char *arr;

    #ifdef BONUS
    arr =  "1s2";
    #else
    arr = "1s";
    #endif
    while (l != NULL && p.y < game->parser->lines.index)
    {
         l = game->parser->lines.get(&game->parser->lines, p.y );
        while (ft_strchr(arr,l[(int) p.x]) != NULL&& 
        l[(int)p.x - 1] != '1' && l[(int)p.x - 1] != '2')
        {
            p.y += 1;
            l = game->parser->lines.get(&game->parser->lines, p.y);
            if (l != NULL)
            {
                len = ft_strlen(l);
                if (p.x >= len)
                    break;
            }
            else 
                break;
        }

            if (start.y < p.y)
                {

                   game->walls.push(&(game->walls),new_wall(new_vector_pointer((start.x ) * game->wvalue, (start.y )*game->hvalue),new_vector_pointer((p.x)* game->wvalue ,(p.y )*game->hvalue),1), sizeof(t_wall));
                 //   printf("this is xx %d",xx);
                }
                 p.y += 1;
                 start.x = p.x;
                 start.y = p.y;
    }
}
